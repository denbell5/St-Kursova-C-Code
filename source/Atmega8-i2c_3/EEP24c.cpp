#include "main.h"

// запись байта
uint8_t eep_write_byte(uint16_t address,uint8_t byte) {
	uint8_t status;
	status=i2c_start();

	if (status==TWI_OK)
	{
		status=i2c_send_addr(EEP24C_WRITE);

		if (status==TWI_OK)
		{
			status=i2c_send_byte(address>>8); // старшие 8 бит

			if (status==TWI_OK)
			{
				status=i2c_send_byte(address); // младшие 8 бит

				if (status==TWI_OK)
				{
					status=i2c_send_byte(byte); // отправка байта

				}
			}
		}
		i2c_stop();
	}
	_delay_ms(5);
	return status;
}



// чтение байта
uint8_t eep_read_byte(uint16_t address, uint8_t *byte) {
	uint8_t status;
	
	status=i2c_start();
	if (status==TWI_OK)
	{
		status=i2c_send_addr(EEP24C_WRITE);
		if (status==TWI_OK)
		{
			status=i2c_send_byte(address>>8); // старшие 8 бит
			if (status==TWI_OK)
			{
				status=i2c_send_byte(address); // младшие 8 бит
				if (status==TWI_OK)
				{
					status=i2c_start();
					if (status==TWI_OK)
					{
						status=i2c_send_addr(EEP24C_READ);
						if (status==TWI_OK)
						{
							status=i2c_read_byte((uint8_t*)byte, 0);
						}
					}
				}
			}
		}
		i2c_stop();
	}
	return status;	
}

//запись 8 битного массива. startaddress - адрес начальной €чейки,  massiv - им€ массива, col - кличество байт в массиве
uint8_t eep_write_8massiv(uint16_t startaddress,uint8_t *massiv, uint8_t col) {
	uint8_t status;
	status=i2c_start();
	if (status==TWI_OK)
	{
		status=i2c_send_addr(EEP24C_WRITE);
		if (status==TWI_OK)
		{
			status=i2c_send_byte(startaddress>>8); // старшие 8 бит
			if (status==TWI_OK)
			{
				status=i2c_send_byte(startaddress); // младшие 8 бит
				if (status==TWI_OK)
				{
					for (uint8_t i=0; i<col; i++)
					{
						status=i2c_send_byte(massiv[i]);
						if (status!=TWI_OK) break;
					}
				}
			}
		}
	}
	i2c_stop();
	return status;
}

// чтение 8 битного массива
uint8_t eep_read_8massiv(uint16_t startaddress,uint8_t *massiv, uint8_t col) {
	uint8_t status;
	status=i2c_start();
	if (status==TWI_OK)
	{
		status=i2c_send_addr(EEP24C_WRITE);
		if (status==TWI_OK)
		{
			status=i2c_send_byte(startaddress>>8);
			if (status==TWI_OK)
			{
				status=i2c_send_byte(startaddress);
				if (status==TWI_OK)
				{
					status=i2c_start();
					if (status==TWI_OK)
					{
						status=i2c_send_addr(EEP24C_READ);
						if (status==TWI_OK)
						{
							for (uint8_t i=0; i<col-1; i++)
							{
								status=i2c_read_byte(&massiv[i],1);
								if (status!=TWI_OK) break;
							}
							if (status==TWI_OK)
							{
								status=i2c_read_byte(&massiv[col-1],0);
							}
						}
					}
				}
			}
		}
	}
	i2c_stop();
	return status;
}