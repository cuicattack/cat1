#ifndef SENSOR_H
#define SENSOR_H
#define SENSOR_READ 0x01
#define SENSOR_WRITE 0x00

void sensor_init(void);
uint8_t sensor_start(uint8_t address);
uint8_t sensor_write(uint8_t data);
uint8_t sensor_read_ack(void);
uint8_t sensor_read_nack(void);
uint8_t sensor_transmit(uint8_t address, uint8_t* data, uint16_t length);
uint8_t sensor_receive(uint8_t address, uint8_t* data, uint16_t length);
uint8_t sensor_writeReg(uint8_t devaddr, uint8_t regaddr, uint8_t* data, uint16_t length);
uint8_t sensor_readReg(uint8_t devaddr, uint8_t regaddr, uint8_t* data, uint16_t length);
void sensor_stop(void);

#endif // I2C_MASTER_H
