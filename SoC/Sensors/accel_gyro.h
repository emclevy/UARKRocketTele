/*
 * accel_gyro.h
 *
 *  Created on: Apr 16, 2023
 *      Author: troyjones
 */

#ifndef ACCEL_GYRO_H_
#define ACCEL_GYRO_H_

#include <stdint.h>

#define MPU6500_ADDRESS 0x68 // MPU-6500 I2C address (AD0 pin low)

// MPU-6500 Register Addresses
#define MPU6500_PWR_MGMT_1 0x6B
#define MPU6500_CONFIG 0x1A
#define MPU6500_GYRO_CONFIG 0x1B
#define MPU6500_ACCEL_CONFIG 0x1C
#define MPU6500_ACCEL_XOUT_H 0x3B
#define MPU6500_GYRO_XOUT_H 0x43

void MPU6500_init();
void MPU6500_read_accel_gyro(int16_t *ax, int16_t *ay, int16_t *az, int16_t *gx, int16_t *gy, int16_t *gz);

#endif /* ACCEL_GYRO_H_ */
