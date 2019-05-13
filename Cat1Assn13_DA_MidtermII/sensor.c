#ifndef  F_CPU
#define F_CPU 8000000UL
#endif
#include <avr/io.h>
#include <util/twi.h>
#include "sensor.h"
#define F_SCL 100000UL // SCL frequency
#define Prescaler 1
#define TWBR_val ((((F_CPU / F_SCL) / Prescaler) - 16 ) / 2)

void sensor_init(void)
{
	TWBR = (uint8_t)TWBR_val;
}
uint8_t sensor_read_nack(void)
{
	TWCR = (1<<TWINT) | (1<<TWEN);// start receiving without acknowledging reception
	while( !(TWCR & (1<<TWINT)) );// wait for end of transmission
	return TWDR;// return received data from TWDR
}
uint8_t sensor_transmit(uint8_t address, uint8_t* data, uint16_t length)
{
	if (sensor_start(address | I2C_WRITE)) return 1;
	for (uint16_t i = 0; i < length; i++)
	{
		if (sensor_write(data[i])) return 1;
	}
	sensor_stop();
	return 0;
}
uint8_t sensor_receive(uint8_t address, uint8_t* data, uint16_t length)
{
	if (sensor_start(address | I2C_READ)) return 1;
	for (uint16_t i = 0; i < (length-1); i++)
	{
		data[i] = sensor_read_ack();
	}
	data[(length-1)] = sensor_read_nack();
	sensor_stop();
	return 0;
}
uint8_t sensor_start(uint8_t address)
{
	TWCR = 0;// reset TWI control register
	TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);// transmit START condition
	while( !(TWCR & (1<<TWINT)) ); // wait for end of transmission
	if((TWSR & 0xF8) != TW_START){ return 1; }// check if the start condition was successfully transmitted
	TWDR = address;// load slave address into data register
	TWCR = (1<<TWINT) | (1<<TWEN); // start transmission of address
	while( !(TWCR & (1<<TWINT)) );// wait for end of transmission
	uint8_t twst = TW_STATUS & 0xF8;// check if the device has acknowledged the READ / WRITE mode
	if ( (twst != TW_MT_SLA_ACK) && (twst != TW_MR_SLA_ACK) ) return 1;
	return 0;
}
uint8_t sensor_write(uint8_t data)
{
	TWDR = data;// load data into data register
	TWCR = (1<<TWINT) | (1<<TWEN);// start transmission of data
	while( !(TWCR & (1<<TWINT)) );// wait for end of transmission
	if( (TWSR & 0xF8) != TW_MT_DATA_ACK ){ return 1; }
	return 0;
}
uint8_t sensor_read_ack(void)
{
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWEA); // start TWI module and acknowledge data after reception
	while( !(TWCR & (1<<TWINT)) );// wait for end of transmission
	return TWDR;// return received data from TWDR
}
uint8_t sensor_writeReg(uint8_t devaddr, uint8_t regaddr, uint8_t* data, uint16_t length)
{
	if (sensor_start(devaddr | 0x00)) return 1;
	sensor_write(regaddr);
	for (uint16_t i = 0; i < length; i++)
	{
		if (sensor_write(data[i])) return 1;
	}
	sensor_stop();
	return 0;
}
uint8_t sensor_readReg(uint8_t devaddr, uint8_t regaddr, uint8_t* data, uint16_t length)
{
	if (sensor_start(devaddr)) return 1;
	sensor_write(regaddr);
	if (sensor_start(devaddr | 0x01)) return 1;
	for (uint16_t i = 0; i < (length-1); i++)
	{
		data[i] = sensor_read_ack();
	}
	data[(length-1)] = sensor_read_nack();
	sensor_stop();

	return 0;
}
void sensor_stop(void)
{
	// transmit STOP condition
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO);
}
