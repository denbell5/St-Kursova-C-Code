/*
 * TC74.cpp
 *
 * Created: 3/26/2020 2:49:06 PM
 *  Author: denbe
 */ 
#include "main.h"
bool TC74_IsReady()
{
	uint8_t status;
	status = i2c_start();
	status = i2c_send_addr(TC74_WRITE);
	status = i2c_send_byte(0x01);
	
	status = i2c_start();
	status = i2c_send_addr(TC74_READ);
	
	uint8_t data = i2c_readNak();
	if(data & TC74_DATA_READY)
	{
		return true;
	}
	else
	{
		return false;
	}
}
void TC74_write(uint8_t data)
{
	i2c_start();
	i2c_send_addr(TC74_WRITE); // адресс датчика
	i2c_send_byte(0x01); // адресс регистра конфигурации
	i2c_send_byte(data); // данные в регистр
	i2c_stop();
}

uint8_t TC74_read()
{
	uint8_t status;
	status = i2c_start();
	status = i2c_send_addr(TC74_WRITE);
	status = i2c_send_byte(0x00);
	status = i2c_start();
	status = i2c_send_addr(TC74_READ);
	uint8_t data = i2c_readNak();
	uart_send_byte(data);
	i2c_stop();
	return data;
}
