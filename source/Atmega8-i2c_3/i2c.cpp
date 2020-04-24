#include "main.h"

// инициализация
void i2c_init(void) {
	TWSR = 0; // для простоты расчетов 0.
	TWBR = ((F_CPU/I2C_SPEED)-16)/2;  // рассчитываем значение регистра TWBR
}

// ожидание
void i2c_wait(void)
{
	while (!(TWCR & (1<<TWINT)));
}

// старт
uint8_t i2c_start(void)
{
	uint8_t status = TWI_OK;
	
	TWCR = (1<<TWEN)|(1<<TWINT)|(1<<TWSTA);
	i2c_wait();
	status = TWSR & TWSR_MASK;
	if ((status != TWI_START) && (status != TWI_REP_START)){
		return status;
	}
	return TWI_OK;
}

// стоп
void i2c_stop(void)
{
	TWCR = (1<<TWEN)|(1<<TWINT)|(1<<TWSTO);
}

// отправка адреса
uint8_t i2c_send_addr(uint8_t address)
{
	uint8_t status;
	
	i2c_wait();
	TWDR = address;
	TWCR = (1<<TWINT)|(1<<TWEN);
	i2c_wait();
	status = TWSR & TWSR_MASK;
	if ((status != TWI_MTX_ADR_ACK) && (status != TWI_MRX_ADR_ACK)){
		return status;
	}
	return TWI_OK;
}

// отправка байта
uint8_t i2c_send_byte(uint8_t byte)
{
	uint8_t status;
	
	i2c_wait();
	TWDR = byte;
	TWCR = (1<<TWINT)|(1<<TWEN);
	i2c_wait();
	status = TWSR & TWSR_MASK;
	if (status != TWI_MTX_DATA_ACK){
		return status;
	}
	return TWI_OK;
}

// чтение байта. ack=0/1 - NACK/ACK
uint8_t i2c_read_byte(uint8_t *byte, uint8_t ack)
{
	uint8_t status;
	
	i2c_wait();
	TWCR = (1<<TWINT)|(1<<TWEN)|((ack & 1) << TWEA);
	i2c_wait();
	*byte = TWDR;
	status = TWSR & TWSR_MASK;
	
	if ((ack && (status != TWI_MRX_DATA_ACK))||(!ack && (status != TWI_MRX_DATA_NACK))){
		return status;
	}
	return TWI_OK;
}

unsigned char i2c_readAck(void) {
	TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
	while (!(TWCR & (1 << TWINT))) {
	}

	return TWDR;
}

unsigned char i2c_readNak(void) {
	TWCR = (1 << TWINT) | (1 << TWEN);
	while (!(TWCR & (1 << TWINT))) {
	}
	
	return TWDR;
}