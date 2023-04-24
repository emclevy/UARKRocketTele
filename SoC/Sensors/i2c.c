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
  UCB1CTL1 |= UCSWRST; // Enable SW reset
  UCB1CTL0 = UCMST + UCMODE_3 + UCSYNC; // I2C Master, synchronous mode
  UCB1CTL1 = UCSSEL_2 + UCSWRST; // Use SMCLK, keep SW reset
  UCB1BR0 = 120; // fSCL = SMCLK/80 = ~200kHz
  UCB1BR1 = 0;
  UCB1CTL1 &= ~UCSWRST; // Clear SW reset, resume operation
  //UCB1IE |= UCTXIE + UCRXIE; // Enable TX and RX interrupts
}

void i2c_start()
{
  // Generate a START condition
  UCB1CTL1 |= UCTR + UCTXSTT; // I2C TX, START condition
}

void i2c_stop()
{
  // Generate a STOP condition
  UCB1CTL1 |= UCTXSTP; // I2C STOP condition
  while (UCB1CTL1 & UCTXSTP); // Wait for STOP condition
}

void i2c_write(uint8_t addr, uint8_t reg, uint8_t *data, uint8_t len)
{
    UCB1I2CSA = addr;

    UCB1CTL1 |= UCTR | UCTXSTT; // Transmit mode and send start condition

    //while (!(UCB1IFG & UCTXIFG));
    UCB1TXBUF = reg;

    uint8_t i = 0;
    for (i; i < len; i++)
    {
        //while (!(UCB1IFG & UCTXIFG));
        UCB1TXBUF = data[i];
    }

    //while (!(UCB1IFG & UCTXIFG));
    UCB1CTL1 |= UCTXSTP; // Send stop condition

    while (UCB1CTL1 & UCTXSTP);
}

void i2c_read(uint8_t addr, uint8_t reg, uint8_t *data, uint8_t len)
{
    UCB1I2CSA = addr;

    UCB1CTL1 |= UCTR | UCTXSTT; // Transmit mode and send start condition

    //while (!(UCB1IFG & UCTXIFG));
    UCB1TXBUF = reg;

    //while (!(UCB1IFG & UCTXIFG));
    UCB1CTL1 &= ~UCTR; // Receive mode
    UCB1CTL1 |= UCTXSTT; // Send repeated start condition


    uint8_t i = 0;
    for (i; i < len - 1; i++)
    {
        while (!(UCB1IFG & UCRXIFG));
        data[i] = UCB1RXBUF;
    }

    UCB1CTL1 |= UCTXSTP; // Send stop condition
    //while (!(UCB1IFG & UCRXIFG));
    data[len - 1] = UCB1RXBUF;

    //while (UCB1CTL1 & UCTXSTP);
}
