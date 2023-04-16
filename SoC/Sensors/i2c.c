/*
 * i2c.c
 *
 *  Created on: Apr 16, 2023
 *      Author: troyjones
 */

#include "i2c.h"
#include <msp430.h>

void i2c_init()
{
  // Configure I2C pins
  P4SEL |= BIT1 | BIT2; // Assign I2C pins to USCI_B0 IMU/ALT_SCL and SDA is on pins 4.1/4.2

  // Configure USCI_B0 for I2C mode
  UCB0CTL1 |= UCSWRST; // Enable SW reset
  UCB0CTL0 = UCMST + UCMODE_3 + UCSYNC; // I2C Master, synchronous mode
  UCB0CTL1 = UCSSEL_2 + UCSWRST; // Use SMCLK, keep SW reset
  UCB0BR0 = 80; // fSCL = SMCLK/80 = ~200kHz
  UCB0BR1 = 0;
  UCB0CTL1 &= ~UCSWRST; // Clear SW reset, resume operation
  UCB0IE |= UCTXIE + UCRXIE; // Enable TX and RX interrupts
}

void i2c_start()
{
  // Generate a START condition
  UCB0CTL1 |= UCTR + UCTXSTT; // I2C TX, START condition
}

void i2c_stop()
{
  // Generate a STOP condition
  UCB0CTL1 |= UCTXSTP; // I2C STOP condition
  while (UCB0CTL1 & UCTXSTP); // Wait for STOP condition
}

void i2c_write(uint8_t addr, uint8_t reg, uint8_t *data, uint8_t len)
{
    UCB0I2CSA = addr;

    UCB0CTL1 |= UCTR | UCTXSTT; // Transmit mode and send start condition

    while (!(UCB0IFG & UCTXIFG));
    UCB0TXBUF = reg;

    for (uint8_t i = 0; i < len; i++)
    {
        while (!(UCB0IFG & UCTXIFG));
        UCB0TXBUF = data[i];
    }

    while (!(UCB0IFG & UCTXIFG));
    UCB0CTL1 |= UCTXSTP; // Send stop condition

    while (UCB0CTL1 & UCTXSTP);
}

void i2c_read(uint8_t addr, uint8_t reg, uint8_t *data, uint8_t len)
{
    UCB0I2CSA = addr;

    UCB0CTL1 |= UCTR | UCTXSTT; // Transmit mode and send start condition

    while (!(UCB0IFG & UCTXIFG));
    UCB0TXBUF = reg;

    while (!(UCB0IFG & UCTXIFG));
    UCB0CTL1 &= ~UCTR; // Receive mode
    UCB0CTL1 |= UCTXSTT; // Send repeated start condition

    for (uint8_t i = 0; i < len - 1; i++)
    {
        while (!(UCB0IFG & UCRXIFG));
        data[i] = UCB0RXBUF;
    }

    UCB0CTL1 |= UCTXSTP; // Send stop condition
    while (!(UCB0IFG & UCRXIFG));
    data[len - 1] = UCB0RXBUF;

    while (UCB0CTL1 & UCTXSTP);
}
