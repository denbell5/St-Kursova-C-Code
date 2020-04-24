#include "main.h"

// чтение даты и времени из микросхемы в массив.
uint8_t ds1307_read_time_date(uint8_t *massiv)
{
	uint8_t status;
	status=i2c_start();
	if (status==TWI_OK)
	{
		status=i2c_send_addr(DS1307_WRITE); // сначала адрес на запись чтобы передать регистр
		if (status==TWI_OK)
		{
			status=i2c_send_byte(SEC_ADDR);// начинаем с адреса регистра секунд
			if (status==TWI_OK)
			{
				status=i2c_start();
				if (status==TWI_OK)
				{
					status=i2c_send_addr(DS1307_READ);// переключаемся на чтение
					if (status==TWI_OK)
					{
						for (uint8_t i=0; i<6; i++)// 6 байт с аск
						{
							status=i2c_read_byte(&massiv[i],1);
							massiv[i] = bcd2dec(massiv[i]);
							if (status!=TWI_OK) break;
						}
						if (status==TWI_OK)
						{
							status=i2c_read_byte(&massiv[6],0);// последний без аск
							massiv[6]= bcd2dec(massiv[6]);
						}
					}
				}
			}
		}
	}
	i2c_stop();
	return status;
}


// запись времени hh -часы. mm -минуты.
uint8_t ds1307_write_time(uint8_t hh, uint8_t mm) {
	uint8_t status;
	hh = dec2bcd(hh);// конвертим значение часов в двоично десятичное 
	mm = dec2bcd(mm);// тоже для минут
	status=i2c_start();
	if (status==TWI_OK)
	{
		status=i2c_send_addr(DS1307_WRITE);
		if (status==TWI_OK)
		{
			status=i2c_send_byte(SEC_ADDR); // снова начнем с секунд
			if (status==TWI_OK)
			{
				status=i2c_send_byte(0); // обнуляем секунды
				if (status==TWI_OK)
				{
					status=i2c_send_byte(mm); // пишем минуты т.к. следующий регистр минутный
					if (status==TWI_OK)
					{
						status=i2c_send_byte(hh); // пишем часы
					}
				}
			}
		}
	}
	i2c_stop();
	return status;
}


// запись даты
uint8_t ds1307_write_date(uint8_t week, uint8_t day, uint8_t month, uint8_t year)  {
	uint8_t status;
	day = dec2bcd(day);// конвертим значение  в BCD
	month = dec2bcd(month);// для месяца
	year = dec2bcd(year);// тоже для года
	status=i2c_start();
	if (status==TWI_OK)
	{
		status=i2c_send_addr(DS1307_WRITE);
		if (status==TWI_OK)
		{
			status=i2c_send_byte(WEEK_ADDR); // начнем с дня недели
			if (status==TWI_OK)
			{
				status=i2c_send_byte(week); // 
				if (status==TWI_OK)
				{
					status=i2c_send_byte(day); // 
					if (status==TWI_OK)
					{
						status=i2c_send_byte(month); // 
						if (status==TWI_OK)
						{
							status=i2c_send_byte(year);
						}
					}
				}
			}
		}
	}
	i2c_stop();
	return status;
}


// остановка-запуск часов
uint8_t ds1307_clock_stop(uint8_t onoff) {
	uint8_t status;
	uint8_t sec_dump;// для сохранения секунд
	
	status=i2c_start();
	if (status==TWI_OK)
	{
		status=i2c_send_addr(DS1307_WRITE);
		if (status==TWI_OK)
		{
			status=i2c_send_byte(SEC_ADDR); // бит остановки/страта часов в регистре секунд - старший бит
			if (status==TWI_OK)
			{
				status=i2c_start();
				if (status==TWI_OK)
				{
					status=i2c_send_addr(DS1307_READ);// на чтение т.к. прочитаем секунды для начала.
					if (status==TWI_OK)
					{
						status=i2c_read_byte(&sec_dump,0);
						i2c_stop();
						if (status==TWI_OK)
						{
							if (onoff)
							{
								sec_dump|=(1<<7);
								} else {
								sec_dump&=~(1<<7);
							}
							status=i2c_start();
							if (status==TWI_OK)
							{
								status=i2c_send_addr(DS1307_WRITE);
								if (status==TWI_OK)
								{
									status=i2c_send_byte(SEC_ADDR);
									if (status==TWI_OK)
									{
										status=i2c_send_byte(sec_dump);
									}
								}
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


//
uint8_t ds1307_sq(uint8_t byte) {
	uint8_t status;
	status=i2c_start();
	if (status==TWI_OK)
	{
		status=i2c_send_addr(DS1307_WRITE);
		if (status==TWI_OK)
		{
			status=i2c_send_byte(CONTROL_ADDR);
			if (status==TWI_OK)
			{
				status=i2c_send_byte(byte);
			}
		}
	}
	i2c_stop();
	return status;
}


// конверт BCD в десятичное
uint8_t bcd2dec(uint8_t val) {
	return val - 6 * (val >> 4);
}

// конверт десятичное в BCD
uint8_t dec2bcd(uint8_t val) {
	return ((val/10)<<4) + val%10;
}