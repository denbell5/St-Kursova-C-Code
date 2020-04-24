#include "main.h"

// volatile uint8_t temp;




int main(void)
{	
	uint16_t capacitance;
	uint16_t measuredMsb;
	uint16_t measuredLsb;
	uint8_t temp;
	uint8_t date_time[7]; // ������ ��� �����
	uint16_t counter; // ������ ��������� ���������� ������
	
	i2c_init(); // �2� ���.
	uart_init(MYUBRR); // ���� ���.
	// _delay_ms(200);
	
	
	
	// ������������� FCD      CAPDC
					 // 5432109876543210
	fcd_write16(0x08, 0b0001000101100000); // � MEAS1_CONF
	fcd_write16(0x0C, 0b0000000010000000); // FDC_CONF
	//_delay_ms(9);
	
	counter = iEEPROM_read16(0x00);
	
	while (1)
	{	
		
		// ����������� ��������� � ��������� ���� ��� ����������
		fcd_write16(0x0C, 0b0000000010000000);
		while((FDC1004_read(0x0C) & 0b0000000000001000) != 0b0000000000001000)
		{
			_delay_ms(9);
		}
		
		// ��������� ���������� ���������
		measuredMsb = FDC1004_read(0x00);
		measuredLsb = FDC1004_read(0x01);
		
		// ��������� ������� ��� ����� �����������
		capacitance = CalculateCapacitance(measuredMsb, measuredLsb);
		
		// ��������� ����������� 
		while(!(TC74_IsReady()));
		temp = TC74_read();
		
		// ������ ����������� ��������� ��-�� �����������
		capacitance = IncludeTemperatureOffset(temp, capacitance);
		
		// ������� ���� � �����
		ds1307_read_time_date(date_time);
		
		// �������� ���� � ����� � ������
		eep_write_byte(counter, date_time[4]); // �����
		eep_write_byte(counter+1, date_time[5]); // �����
		eep_write_byte(counter+2, date_time[6]); // ���
		eep_write_byte(counter+3, date_time[2]); // ���
		eep_write_byte(counter+4, date_time[1]); // ������
		eep_write_byte(counter+5, date_time[0]); // �������
		// �������� ������� � ������
		eep_write_byte(counter+6, capacitance >> 8 );
		eep_write_byte(counter+7, capacitance );
		
		// ��������� ������� � �������� ��� � ������ ��
		counter+=8;
		iEEPROM_write16(0x00, counter);
	
		// ������ 5 ������
		_delay_ms(4949);			
	}	
}
uint16_t IncludeTemperatureOffset(uint8_t temperature, uint16_t capacitance)
{
	if(IsTemperatureNegative(temperature) || temperature < 20)
	{
		return capacitance - 2;
	}
	else if(60 < temperature && temperature < 100 )
	{
		return capacitance + 2;
	}
	else if(temperature > 100)
	{
		return capacitance - 4;
	}
	else
	{
		return capacitance;
	}
}
bool IsTemperatureNegative(uint8_t data)
{
	uint8_t a = 0x80;
	
	if((a & data) == a)
	{
		return true;
	}
	else
	{
		return false;
	}
}
uint16_t CalculateCapacitance(uint16_t data1, uint16_t data2)
{
	uint16_t a = 0x8000; // ��� �������� ����� (� 23 ������� 1 ���, ��� ��������� 0)
	uint32_t data;
	
	// �������� ������� � ������� ���
	data = data1;
	data = data << 16;
	data |= data2;
	//
	// ���� ������������� ����� - ���������� �� ���. ���� � ������
	if((a & data1) == a)
	{
		data = data - 0b1; // ������ �������
		data = ~data; // �������������
		data = data >> 8; // ��������� �� 24 ��������
		
		data = data * 100; // ��� ���������� ������ �� �����
		
		data = data / 0x80000; // �������� ������� � �����������
		data = 3437 - data; // ������ �������� ��������� (CAPDAC)
	}
	else
	{
		data = data >> 8; // ��������� �� 24 ��������
		
		data = data * 100; // ��� ���������� ������ �� �����
		
		data = data / 0x80000; // ���������� ������� � �����������
		data = 3437 + data; // ������ �������� ��������� (CAPDAC)
	}
	
	return (uint16_t)data; // ������� ������� 16 ���
}

void ResetEEP()
{
	for (int i=0; i < 4092; i++)
	{
		eep_write_byte(i, 0xcc);

	}
}