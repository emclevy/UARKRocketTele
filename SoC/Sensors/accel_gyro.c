/*
 * accel_gyro.c
 *
 *  Created on: Apr 16, 2023
 *      Author: troyjones
 */

#include "accel_gyro.h"
#include <msp430.h>
#include "i2c.h"

// Define MPU-6500 registers, I2C address, and other constants here

void MPU6500_init()
{
    // Initialize the I2C interface
    i2c_init();

    // Write the necessary configuration to MPU-6500 registers
    i2c_write(MPU6500_ADDRESS, MPU6500_PWR_MGMT_1, (uint8_t[]){0x00}, 1); // Reset device and wake from sleep
    __delay_cycles(10000); // Wait for the device to stabilize

    i2c_write(MPU6500_ADDRESS, MPU6500_CONFIG, (uint8_t[]){0x00}, 1); // Set gyro and temperature DLPF
    i2c_write(MPU6500_ADDRESS, MPU6500_GYRO_CONFIG, (uint8_t[]){0x00}, 1); // Set gyro full scale range
    i2c_write(MPU6500_ADDRESS, MPU6500_ACCEL_CONFIG, (uint8_t[]){0x00}, 1); // Set accelerometer full scale range
}

void MPU6500_read_accel_gyro(int16_t *ax, int16_t *ay, int16_t *az, int16_t *gx, int16_t *gy, int16_t *gz)
{
    uint8_t buffer[14];

    // Read raw accelerometer and gyroscope data from MPU-6500 registers
    i2c_read(MPU6500_ADDRESS, MPU6500_ACCEL_XOUT_H, buffer, 14);

    // Convert raw accelerometer and gyroscope data to actual values
    *ax = (buffer[0] << 8) | buffer[1];
    *ay = (buffer[2] << 8) | buffer[3];
    *az = (buffer[4] << 8) | buffer[5];
    *gx = (buffer[8] << 8) | buffer[9];
    *gy = (buffer[10] << 8) | buffer[11];
    *gz = (buffer[12] << 8) | buffer[13];
}
