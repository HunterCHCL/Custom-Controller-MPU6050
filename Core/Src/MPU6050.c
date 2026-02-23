/**
  ******************************************************************************
  * @file    MPU6050.c
  * @brief   Source file for MPU6050 driver
  ******************************************************************************
  */

#include "MPU6050.h"

// Internal function to write a byte to a register
HAL_StatusTypeDef MPU6050_Write_Reg(uint8_t reg, uint8_t data) {
    return HAL_I2C_Mem_Write(&hi2c1, MPU6050_ADDR, reg, I2C_MEMADD_SIZE_8BIT, &data, 1, HAL_MAX_DELAY);
}

// Internal function to read a byte from a register
HAL_StatusTypeDef MPU6050_Read_Reg(uint8_t reg, uint8_t *data) {
    return HAL_I2C_Mem_Read(&hi2c1, MPU6050_ADDR, reg, I2C_MEMADD_SIZE_8BIT, data, 1, HAL_MAX_DELAY);
}

// Internal function to read multiple bytes
HAL_StatusTypeDef MPU6050_Read_Regs(uint8_t reg, uint8_t *data, uint8_t len) {
    return HAL_I2C_Mem_Read(&hi2c1, MPU6050_ADDR, reg, I2C_MEMADD_SIZE_8BIT, data, len, HAL_MAX_DELAY);
}

/**
 * @brief  Initialize MPU6050
 * @param  gyro_sens: Gyroscope sensitivity (MPU6050_GYRO_SENS_250, etc.)
 * @param  accel_sens: Accelerometer sensitivity (MPU6050_ACCEL_SENS_2G, etc.)
 * @retval HAL status
 */
HAL_StatusTypeDef MPU6050_Init(uint8_t gyro_sens, uint8_t accel_sens) {
    HAL_StatusTypeDef status;

    // Wake up the sensor
    status = MPU6050_Write_Reg(MPU6050_REG_PWR_MGMT_1, 0x00);
    if (status != HAL_OK) return status;

    HAL_Delay(100); // Wait for sensor to stabilize

    // Set sample rate divider
    status = MPU6050_Write_Reg(MPU6050_REG_SMPLRT_DIV, 0x07);
    if (status != HAL_OK) return status;

    // Set gyroscope configuration
    status = MPU6050_Write_Reg(MPU6050_REG_GYRO_CONFIG, gyro_sens);
    if (status != HAL_OK) return status;

    // Set accelerometer configuration
    status = MPU6050_Write_Reg(MPU6050_REG_ACCEL_CONFIG, accel_sens);
    if (status != HAL_OK) return status;

    // Configure low pass filter
    status = MPU6050_Write_Reg(MPU6050_REG_CONFIG, 0x00);
    if (status != HAL_OK) return status;

    return HAL_OK;
}

/**
 * @brief  Read all sensor data
 * @param  data: Pointer to MPU6050_t structure
 * @retval HAL status
 */
HAL_StatusTypeDef MPU6050_Read_All(MPU6050_t *data) {
    uint8_t buffer[14];
    HAL_StatusTypeDef status;

    status = MPU6050_Read_Regs(MPU6050_REG_ACCEL_XOUT_H, buffer, 14);
    if (status != HAL_OK) return status;

    data->Accel_X = (int16_t)(buffer[0] << 8 | buffer[1]);
    data->Accel_Y = (int16_t)(buffer[2] << 8 | buffer[3]);
    data->Accel_Z = (int16_t)(buffer[4] << 8 | buffer[5]);
    data->Temp = (int16_t)(buffer[6] << 8 | buffer[7]);
    data->Gyro_X = (int16_t)(buffer[8] << 8 | buffer[9]);
    data->Gyro_Y = (int16_t)(buffer[10] << 8 | buffer[11]);
    data->Gyro_Z = (int16_t)(buffer[12] << 8 | buffer[13]);

    return HAL_OK;
}

/**
 * @brief  Read accelerometer data
 * @param  data: Pointer to MPU6050_t structure
 * @retval HAL status
 */
HAL_StatusTypeDef MPU6050_Read_Accel(MPU6050_t *data) {
    uint8_t buffer[6];
    HAL_StatusTypeDef status;

    status = MPU6050_Read_Regs(MPU6050_REG_ACCEL_XOUT_H, buffer, 6);
    if (status != HAL_OK) return status;

    data->Accel_X = (int16_t)(buffer[0] << 8 | buffer[1]);
    data->Accel_Y = (int16_t)(buffer[2] << 8 | buffer[3]);
    data->Accel_Z = (int16_t)(buffer[4] << 8 | buffer[5]);

    return HAL_OK;
}

/**
 * @brief  Read gyroscope data
 * @param  data: Pointer to MPU6050_t structure
 * @retval HAL status
 */
HAL_StatusTypeDef MPU6050_Read_Gyro(MPU6050_t *data) {
    uint8_t buffer[6];
    HAL_StatusTypeDef status;

    status = MPU6050_Read_Regs(MPU6050_REG_GYRO_XOUT_H, buffer, 6);
    if (status != HAL_OK) return status;

    data->Gyro_X = (int16_t)(buffer[0] << 8 | buffer[1]);
    data->Gyro_Y = (int16_t)(buffer[2] << 8 | buffer[3]);
    data->Gyro_Z = (int16_t)(buffer[4] << 8 | buffer[5]);

    return HAL_OK;
}

/**
 * @brief  Read temperature data
 * @param  data: Pointer to MPU6050_t structure
 * @retval HAL status
 */
HAL_StatusTypeDef MPU6050_Read_Temp(MPU6050_t *data) {
    uint8_t buffer[2];
    HAL_StatusTypeDef status;

    status = MPU6050_Read_Regs(MPU6050_REG_TEMP_OUT_H, buffer, 2);
    if (status != HAL_OK) return status;

    data->Temp = (int16_t)(buffer[0] << 8 | buffer[1]);

    return HAL_OK;
}

/**
 * @brief  Read all sensor data as int16_t array
 * @param  data: Pointer to int16_t array (must have at least 7 elements)
 *         Order: Accel_X, Accel_Y, Accel_Z, Temp, Gyro_X, Gyro_Y, Gyro_Z
 * @retval HAL status
 */
HAL_StatusTypeDef MPU6050_Read_All_Int16(int16_t *data) {
    uint8_t buffer[14];
    HAL_StatusTypeDef status;

    status = MPU6050_Read_Regs(MPU6050_REG_ACCEL_XOUT_H, buffer, 14);
    if (status != HAL_OK) return status;

    data[0] = (int16_t)(buffer[0] << 8 | buffer[1]);  // Accel_X
    data[1] = (int16_t)(buffer[2] << 8 | buffer[3]);  // Accel_Y
    data[2] = (int16_t)(buffer[4] << 8 | buffer[5]);  // Accel_Z
    data[3] = (int16_t)(buffer[6] << 8 | buffer[7]);  // Temp
    data[4] = (int16_t)(buffer[8] << 8 | buffer[9]);  // Gyro_X
    data[5] = (int16_t)(buffer[10] << 8 | buffer[11]); // Gyro_Y
    data[6] = (int16_t)(buffer[12] << 8 | buffer[13]); // Gyro_Z

    return HAL_OK;
}