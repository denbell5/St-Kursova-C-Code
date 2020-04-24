/*
 * FCD1004.cpp
 *
 * Created: 3/14/2020 1:23:02 PM
 *  Author: denbe
 */ 
#include "FCD1004.h"

uint8_t fcd_write16(uint8_t reg, uint16_t data)
{
	uint8_t status;
	status=i2c_start(); // ������ ����
	if(status==TWI_OK)
	{
		status = i2c_send_addr(FCD1004_WRITE); // ������ FCD � ����� �� ������
		if(status==TWI_OK)
		{
			// ������ ��������, � ������� ���� �������� ������
			status = i2c_send_byte(reg); 
			if(status==TWI_OK)
			{
				// ������ ���� ������ (MSB)
				status = i2c_send_byte((uint8_t) (data >> 8)); 
				if(status==TWI_OK)
				{
					// ������ ���� ������ (LSB)
					status = i2c_send_byte(data);
				}
			}
		}
	}
	i2c_stop();
	return status;
}

uint8_t fcd_read16(uint8_t reg, uint8_t *MLSB)
{
	uint8_t status;
	status=i2c_start();
	// ������ ���������� � ����� ������
	status = i2c_send_addr(FCD1004_WRITE);
	// ������ ��������, �� �������� ����� ������
	status = i2c_send_byte(reg);
	// ��������� � ������ ����		
	// i2c_stop();
	status = i2c_start();
	// ������ ���������� � ����� ������ 		
	status = i2c_send_addr(FCD1004_READ);
	_delay_ms(100);
	// ������ ������� �����
	status = i2c_read_byte(&MLSB[0], 1);
	_delay_ms(100);
	// ������ ������� �����	
	status = i2c_read_byte(&MLSB[1], 0);
	_delay_ms(100);				

	i2c_stop();
	return status;
}

uint16_t FDC1004_read(uint8_t reg) {
	// Write register address into register pointer
	i2c_start();
	i2c_send_addr(FCD1004_WRITE);
	i2c_send_byte(reg);

	// Actually read the data back
	uint16_t data = 0;
	i2c_start();
	i2c_send_addr(FCD1004_READ);
	//_delay_ms(1000);
	data  = ((uint16_t)i2c_readAck()) << 8;
	//_delay_ms(1000);
	data |= i2c_readNak();
	//_delay_ms(1000);
	i2c_stop();
	return data;
}

