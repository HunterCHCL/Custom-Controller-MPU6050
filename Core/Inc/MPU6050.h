/**
  ******************************************************************************
  * @file    MPU6050.h
  * @brief   Header file for MPU6050 driver
  ******************************************************************************
  */

#ifndef __MPU6050_H__
#define __MPU6050_H__

#include "main.h"
#include "i2c.h"

// MPU6050 I2C address (AD0 low: 0x68, AD0 high: 0x69)
#define MPU6050_ADDR 0x68 << 1  // Shifted for HAL

// MPU6050 registers
#define MPU6050_REG_SMPLRT_DIV       0x19
#define MPU6050_REG_CONFIG           0x1A
#define MPU6050_REG_GYRO_CONFIG      0x1B
#define MPU6050_REG_ACCEL_CONFIG     0x1C
#define MPU6050_REG_ACCEL_XOUT_H     0x3B
#define MPU6050_REG_ACCEL_XOUT_L     0x3C
#define MPU6050_REG_ACCEL_YOUT_H     0x3D
#define MPU6050_REG_ACCEL_YOUT_L     0x3E
#define MPU6050_REG_ACCEL_ZOUT_H     0x3F
#define MPU6050_REG_ACCEL_ZOUT_L     0x40
#define MPU6050_REG_TEMP_OUT_H       0x41
#define MPU6050_REG_TEMP_OUT_L       0x42
#define MPU6050_REG_GYRO_XOUT_H      0x43
#define MPU6050_REG_GYRO_XOUT_L      0x44
#define MPU6050_REG_GYRO_YOUT_H      0x45
#define MPU6050_REG_GYRO_YOUT_L      0x46
#define MPU6050_REG_GYRO_ZOUT_H      0x47
#define MPU6050_REG_GYRO_ZOUT_L      0x48
#define MPU6050_REG_PWR_MGMT_1       0x6B
#define MPU6050_REG_PWR_MGMT_2       0x6C
#define MPU6050_REG_WHO_AM_I         0x75

// Gyroscope sensitivity
#define MPU6050_GYRO_SENS_250        0
#define MPU6050_GYRO_SENS_500        8
#define MPU6050_GYRO_SENS_1000       16
#define MPU6050_GYRO_SENS_2000       24

// Accelerometer sensitivity
#define MPU6050_ACCEL_SENS_2G        0
#define MPU6050_ACCEL_SENS_4G        8
#define MPU6050_ACCEL_SENS_8G        16
#define MPU6050_ACCEL_SENS_16G       24

typedef struct {
    int16_t Accel_X;
    int16_t Accel_Y;
    int16_t Accel_Z;
    int16_t Temp;
    int16_t Gyro_X;
    int16_t Gyro_Y;
    int16_t Gyro_Z;
} MPU6050_t;

// Function prototypes
HAL_StatusTypeDef MPU6050_Init(uint8_t gyro_sens, uint8_t accel_sens);
HAL_StatusTypeDef MPU6050_Read_All(MPU6050_t *data);
HAL_StatusTypeDef MPU6050_Read_Accel(MPU6050_t *data);
HAL_StatusTypeDef MPU6050_Read_Gyro(MPU6050_t *data);
HAL_StatusTypeDef MPU6050_Read_Temp(MPU6050_t *data);
HAL_StatusTypeDef MPU6050_Read_All_Int16(int16_t *data);

#endif /* __MPU6050_H__ */