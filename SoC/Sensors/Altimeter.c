#include "Altimeter.h"
#include <msp430.h>


/**
 * altimeter.c test
 */
int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    i2c_init();
    // Initialize the timer
    timer_init();

    // Enable global interrupts
    __bis_SR_register(GIE);


    while (1);

    return 0;
}

/**
 * Initialize altimeter
 */
void i2c_init(void)
{
    P4SEL |= BIT1 | BIT2; // Assign I2C pins to USCI_B0 IMU/ALT_SCL and SDA is on pins 4.1/4.2
    UCB0CTL1 |= UCSWRST; // Enable SW reset
    UCB0CTL0 = UCMST | UCMODE_3 | UCSYNC; // I2C master mode, synchronous mode
    UCB0CTL1 = UCSSEL_2 | UCSWRST; // Use SMCLK, keep SW reset
    UCB0BR0 = 80; // Set prescaler for 100kHz <-- not sure what value this needs to be
    UCB0BR1 = 0;
    UCB0CTL1 &= ~UCSWRST; // Clear SW reset, resume operation
}

/**
 * check if sensor is setup or not
 */
bool bmp388_init(void)
{
    uint8_t chip_id = 0;
    i2c_read(BMP388_I2C_ADDR, BMP388_REG_CHIPID, &chip_id, 1);

    if (chip_id != 0x50)
        return false;

    // Add additional configuration if required
    return true;
}

void bmp388_read_coefficients(void)
{
    uint8_t buffer[21];

    i2c_read(BMP388_I2C_ADDR, 0x31, buffer, sizeof(buffer));

    t1 = (buffer[1] << 8) | buffer[0];
    t2 = (buffer[3] << 8) | buffer[2];
    t3 = (buffer[5] << 8) | buffer[4];

    p1 = (buffer[7] << 8) | buffer[6];
    p2 = (buffer[9] << 8) | buffer[8];
    p3 = (buffer[11] << 8) | buffer[10];
    p4 = (buffer[13] << 8) | buffer[12];
    p5 = (buffer[15] << 8) | buffer[14];
    p6 = (buffer[17] << 8) | buffer[16];
    p7 = (buffer[19] << 8) | buffer[18];
    p8 = (buffer[21] << 8) | buffer[20];
    p9 = (buffer[23] << 8) | buffer[22];
}

/*
 * Send the command to start reading data from the sensor
 */
void bmp388_start_measurement(void)
{
    uint8_t cmd = BMP388_CMD_MEASUREMENT; //register for starting reading measurement - defined in data sheet
    i2c_write(BMP388_I2C_ADDR, BMP388_REG_CMD, &cmd, 1);
}

/*
 * Compensate pressure
 */
double bmp388_compensate_pressure(uint32_t raw_pressure, double temperature)
{
    return p1 * (raw_pressure * 0.000001 + p8 * 0.000000001) + p2 * (temperature - p5 * 256);
}


/*
 * Timer and interrupt setup
 */
void timer_init(void)
{
    TA0CCTL0 = CCIE;                // Enable Timer A0 interrupt
    TA0CCR0 = 10000;                // Set interrupt trigger count for 10ms assuming SMCLK is 1 MHz
    TA0CTL = TASSEL_2 + MC_1 + TACLR; // Select SMCLK, up mode, clear TAR
}

/*
 * Altitude timer interrupt
 */
#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A0_ISR(void)
{
    //Calculate Altitude
    if (bmp388_init())
    {
        bmp388_read_coefficients();
        bmp388_start_measurement();

        uint32_t pressure = bmp388_read_pressure();
        uint32_t temperature = bmp388_read_temperature();

        // Calculate altitude and transmit telemetry data
        double pressure = bmp388_compensate_pressure(raw_pressure, temperature);
        double altitude = calculate_altitude(pressure, 101325); //101325 is typical pressure for sea level -- will want to verify that it is 0'd or close to 0 on ground
        printf("%d\n", altitude); //TODO altitude data into the transceiver buffer for send

    }
}
