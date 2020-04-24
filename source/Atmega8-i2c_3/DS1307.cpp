#include "main.h"

// ������ ���� � ������� �� ���������� � ������.
uint8_t ds1307_read_time_date(uint8_t *massiv)
{
	uint8_t status;
	status=i2c_start();
	if (status==TWI_OK)
	{
		status=i2c_send_addr(DS1307_WRITE); // ������� ����� �� ������ ����� �������� �������
		if (status==TWI_OK)
		{
			status=i2c_send_byte(SEC_ADDR);// �������� � ������ �������� ������
			if (status==TWI_OK)
			{
				status=i2c_start();
				if (status==TWI_OK)
				{
					status=i2c_send_addr(DS1307_READ);// ������������� �� ������
					if (status==TWI_OK)
					{
						for (uint8_t i=0; i<6; i++)// 6 ���� � ���
						{
							status=i2c_read_byte(&massiv[i],1);
							massiv[i] = bcd2dec(massiv[i]);
							if (status!=TWI_OK) break;
						}
						if (status==TWI_OK)
						{
							status=i2c_read_byte(&massiv[6],0);// ��������� ��� ���
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


// ������ ������� hh -����. mm -������.
uint8_t ds1307_write_time(uint8_t hh, uint8_t mm) {
	uint8_t status;
	hh = dec2bcd(hh);// ��������� �������� ����� � ������� ���������� 
	mm = dec2bcd(mm);// ���� ��� �����
	status=i2c_start();
	if (status==TWI_OK)
	{
		status=i2c_send_addr(DS1307_WRITE);
		if (status==TWI_OK)
		{
			status=i2c_send_byte(SEC_ADDR); // ����� ������ � ������
			if (status==TWI_OK)
			{
				status=i2c_send_byte(0); // �������� �������
				if (status==TWI_OK)
				{
					status=i2c_send_byte(mm); // ����� ������ �.�. ��������� ������� ��������
					if (status==TWI_OK)
					{
						status=i2c_send_byte(hh); // ����� ����
					}
				}
			}
		}
	}
	i2c_stop();
	return status;
}


// ������ ����
uint8_t ds1307_write_date(uint8_t week, uint8_t day, uint8_t month, uint8_t year)  {
	uint8_t status;
	day = dec2bcd(day);// ��������� ��������  � BCD
	month = dec2bcd(month);// ��� ������
	year = dec2bcd(year);// ���� ��� ����
	status=i2c_start();
	if (status==TWI_OK)
	{
		status=i2c_send_addr(DS1307_WRITE);
		if (status==TWI_OK)
		{
			status=i2c_send_byte(WEEK_ADDR); // ������ � ��� ������
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


// ���������-������ �����
uint8_t ds1307_clock_stop(uint8_t onoff) {
	uint8_t status;
	uint8_t sec_dump;// ��� ���������� ������
	
	status=i2c_start();
	if (status==TWI_OK)
	{
		status=i2c_send_addr(DS1307_WRITE);
		if (status==TWI_OK)
		{
			status=i2c_send_byte(SEC_ADDR); // ��� ���������/������ ����� � �������� ������ - ������� ���
			if (status==TWI_OK)
			{
				status=i2c_start();
				if (status==TWI_OK)
				{
					status=i2c_send_addr(DS1307_READ);// �� ������ �.�. ��������� ������� ��� ������.
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


// ������� BCD � ����������
uint8_t bcd2dec(uint8_t val) {
	return val - 6 * (val >> 4);
}

// ������� ���������� � BCD
uint8_t dec2bcd(uint8_t val) {
	return ((val/10)<<4) + val%10;
}