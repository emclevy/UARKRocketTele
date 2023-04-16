/*
 * Altimeter.h
 *
 *  Created on: Apr 16, 2023
 *      Author: troyjones
 */

#ifndef ALTIMETER_H_
#define ALTIMETER_H_

#include <stdio.h>
#include <msp430.h>
#include <stdint.h>

#define BMP388_I2C_ADDR 0x76
#define BMP388_REG_CHIPID 0x00
#define BMP388_REG_PRESS_MSB 0x04
#define BMP388_REG_TEMP_MSB 0x07
#define BMP388_REG_CMD 0x7E
#define BMP388_CMD_MEASUREMENT 0x59
#define pressure_sea_level 101325

void i2c_init(void);
bool bmp388_init(void);
void bmp388_read_coefficients(void);
void bmp388_start_measurement(void);
uint32_t bmp388_read_pressure(void);
uint32_t bmp388_read_temperature(void);

// Global variables for calibration coefficients
int16_t t1, t2, t3;
int32_t p1, p2, p3, p4, p5, p6, p7, p8, p9;


bool bmp388_init(void);
void bmp388_read_coefficients(void);
void bmp388_start_measurement(void);
double bmp388_compensate_pressure(uint32_t raw_pressure, double temperature);

#endif /* ALTIMETER_H_ */
