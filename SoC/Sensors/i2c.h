/*
 * i2c.h
 *
 *  Created on: Apr 16, 2023
 *      Author: troyjones
 */

#ifndef I2C_H_
#define I2C_H_

#include <stdint.h>

void i2c_init();
void i2c_start();
void i2c_stop();
void i2c_write(uint8_t addr, uint8_t reg, uint8_t *data, uint8_t len);
void i2c_read(uint8_t addr, uint8_t reg, uint8_t *data, uint8_t len);


#endif /* I2C_H_ */
