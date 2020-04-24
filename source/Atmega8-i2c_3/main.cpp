#include "main.h"

// volatile uint8_t temp;




int main(void)
{	
	uint16_t capacitance;
	uint16_t measuredMsb;
	uint16_t measuredLsb;
	uint8_t temp;
	uint8_t date_time[7]; // массив дл€ часов
	uint16_t counter; // адресс последней записанной €чейки
	
	i2c_init(); // и2с ¬ Ћ.
	uart_init(MYUBRR); // уарт ¬ Ћ.
	// _delay_ms(200);
	
	
	
	// »Ќ»÷»јЋ»«ј÷»я FCD      CAPDC
					 // 5432109876543210
	fcd_write16(0x08, 0b0001000101100000); // в MEAS1_CONF
	fcd_write16(0x0C, 0b0000000010000000); // FDC_CONF
	//_delay_ms(9);
	
	counter = iEEPROM_read16(0x00);
	
	while (1)
	{	
		
		// “риггернуть измерение и подождать пока оно выполнитс€
		fcd_write16(0x0C, 0b0000000010000000);
		while((FDC1004_read(0x0C) & 0b0000000000001000) != 0b0000000000001000)
		{
			_delay_ms(9);
		}
		
		// прочитать результаты измерени€
		measuredMsb = FDC1004_read(0x00);
		measuredLsb = FDC1004_read(0x01);
		
		// посчитать емкость без учета температуры
		capacitance = CalculateCapacitance(measuredMsb, measuredLsb);
		
		// прочитать температуру 
		while(!(TC74_IsReady()));
		temp = TC74_read();
		
		// учесть погрешность измерени€ из-за температуры
		capacitance = IncludeTemperatureOffset(temp, capacitance);
		
		// считать дату и врем€
		ds1307_read_time_date(date_time);
		
		// записать дату и врем€ в еепром
		eep_write_byte(counter, date_time[4]); // число
		eep_write_byte(counter+1, date_time[5]); // мес€ц
		eep_write_byte(counter+2, date_time[6]); // год
		eep_write_byte(counter+3, date_time[2]); // час
		eep_write_byte(counter+4, date_time[1]); // минута
		eep_write_byte(counter+5, date_time[0]); // секунда
		// записать емкость в еепром
		eep_write_byte(counter+6, capacitance >> 8 );
		eep_write_byte(counter+7, capacitance );
		
		// увеличить счетчик и записать его в еепром ћ 
		counter+=8;
		iEEPROM_write16(0x00, counter);
	
		// каждые 5 секунд
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
	uint16_t a = 0x8000; // дл€ проверки знака (в 23 разр€де 1 бит, все остальные 0)
	uint32_t data;
	
	// сложение старших и младших бит
	data = data1;
	data = data << 16;
	data |= data2;
	//
	// если отрицательное число - превратить из доп. кода в пр€мой
	if((a & data1) == a)
	{
		data = data - 0b1; // отн€ть единицу
		data = ~data; // инвертировать
		data = data >> 8; // уменьшить до 24 разр€дов
		
		data = data * 100; // дл€ сохранени€ дробей до сотых
		
		data = data / 0x80000; // получить емкость в пикофарадах
		data = 3437 - data; // учесть смещение измерений (CAPDAC)
	}
	else
	{
		data = data >> 8; // уменьшить до 24 разр€дов
		
		data = data * 100; // дл€ сохранени€ дробей до сотых
		
		data = data / 0x80000; // полученить емкость в пикофарадах
		data = 3437 + data; // учесть смещение измерений (CAPDAC)
	}
	
	return (uint16_t)data; // вернуть младшие 16 бит
}

void ResetEEP()
{
	for (int i=0; i < 4092; i++)
	{
		eep_write_byte(i, 0xcc);

	}
}