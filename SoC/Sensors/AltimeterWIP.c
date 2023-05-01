#include "Altimeter.h"
#include "i2c.h"
#include <msp430.h>
#include "driverlib.h"

// https://github.com/boschsensortec/BMP3-Sensor-API/tree/master

/**void clock_init(void)
{
    UCS_setExternalClockSource(0, 12000000);
    UCS_bypassXT2();
    P5SEL |= (BIT2 + BIT3);
    UCS_initClockSignal(UCS_SMCLK, UCS_XT2CLK_SELECT, UCS_CLOCK_DIVIDER_1);
}*/




/**
 * altimeter.c test
 */
int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    init_i2c();
    bmp388_init();
    //clock_init();
    //P4SEL |= BIT1 | BIT2;
    // Initialize the timer
    //timer_init();

    // Enable global interrupts
    __bis_SR_register(GIE);

   uint8_t testData[] = {10,20,30};

    while(1){
        USCI_B_I2C_masterSendSingleByte(USCI_B1_BASE, 0x35); //send single byte

        while(USCI_B_I2C_busBusy(USCI_B0_BASE)); //delay until transmission completes
        //i2c_write(BMP388_I2C_ADDR, 10, testData, 3);
        __delay_cycles(1000);
    }


    /*while (1){
        if (bmp388_init())
            {
                bmp388_read_coefficients();
                bmp388_start_measurement();

                uint32_t raw_pressure = bmp388_read_pressure();
                uint32_t temperature = bmp388_read_temperature();

                // Calculate altitude and transmit telemetry data
                double pressure = bmp388_compensate_pressure(raw_pressure, temperature);
                double altitude = calculate_altitude(pressure, 101325); //101325 is typical pressure for sea level -- will want to verify that it is 0'd or close to 0 on ground
                //printf("%d\n", altitude); //TODO altitude data into the transceiver buffer for send
                __delay_cycles(8000000);
            }
        //else the sensor did not initialize
    }*/

    return 0;
}

/**
 * Initialize altimeter
 */


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
    uint8_t buffer[23];

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

double calculate_altitude(double pressure, double pressure_sea_level_p)
{
    return 44330.0 * (1.0 - pow((pressure / pressure_sea_level_p), 1.0/5.255));
}

uint32_t bmp388_read_pressure(void)
{
    uint8_t buffer[3];
    i2c_read(BMP388_I2C_ADDR, BMP388_REG_PRESS_MSB, buffer, 3);
    return (uint32_t)buffer[0] << 16 | (uint32_t)buffer[1] << 8 | buffer[2];
}

uint32_t bmp388_read_temperature(void)
{
    uint8_t buffer[3];
    i2c_read(BMP388_I2C_ADDR, BMP388_REG_TEMP_MSB, buffer, 3);
    return (uint32_t)buffer[0] << 16 | (uint32_t)buffer[1] << 8 | buffer[2];
}

/*
 * Compensate pressure
 */
double bmp388_compensate_pressure(uint32_t raw_pressure, double temperature)
{
    return p1 * (raw_pressure * 0.000001 + p8 * 0.000000001) + p2 * (temperature - p5 * 256);
}

void init_i2c(void){
    USCI_B_I2C_initMasterParam param_test;
    param_test.selectClockSource = USCI_B_I2C_CLOCKSOURCE_SMCLK;
    param_test.i2cClk = UCS_getSMCLK();
    param_test.dataRate = USCI_B_I2C_SET_DATA_RATE_100KBPS;
    USCI_B_I2C_initMaster(USCI_B1_BASE, &param_test);
    USCI_B_I2C_setSlaveAddress(USCI_B1_BASE, 0x76);
    USCI_B_I2C_setMode(USCI_B1_BASE, USCI_B_I2C_TRANSMIT_MODE);
    USCI_B_I2C_enable(USCI_B1_BASE);
}

void i2c_write(uint8_t reg, uint8_t data)
{
    USCI_B_I2C_setMode(USCI_B1_BASE, USCI_B_I2C_TRANSMIT_MODE);
    USCI_B_I2C_masterSendMultiByteStartWithTimeout(USCI_B1_BASE, reg, USCI_B_I2C_timeout);
    USCI_B_I2C_masterSendMultiByteFinishWithTimeout(USCI_B1_BASE, data, USCI_B_I2C_timeout);
}

void i2c_read(uint8_t reg, uint8_t *data, uint8_t len)
{
    USCI_B_I2C_setMode(USCI_B1_BASE, USCI_B_I2C_TRANSMIT_MODE);
    USCI_B_I2C_masterSendMultiByteStartWithTimeout(USCI_B1_BASE, reg, USCI_B_I2C_timeout);
    USCI_B_I2C_setMode(USCI_B1_BASE, USCI_B_I2C_RECEIVE_MODE);
    USCI_B_I2C_masterReceiveMultiByteStartWithTimeout(USCI_B1_BASE, USCI_B_I2C_timeout);

    uint8_t i = 0;
    for (i; i < len - 1; i++)
    {
        data[i] = USCI_B_I2C_masterReceiveMultiByteNextWithTimeout(USCI_B1_BASE, USCI_B_I2C_timeout);
    }

    data[len - 1] = USCI_B_I2C_masterReceiveMultiByteFinishWithTimeout(USCI_B1_BASE, USCI_B_I2C_timeout);
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

}

