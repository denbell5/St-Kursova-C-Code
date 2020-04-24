#ifndef DS1307_H_
#define DS1307_H_

#define DS1307_WRITE 0b11010000 // адрес дл€ записи
#define DS1307_READ 0b11010001 // адрес дл€ чтени€ 

// адреса регистров
#define SEC_ADDR 0x00
#define MIN_ADRR 0x01
#define HOUR_ADDR 0x02
#define WEEK_ADDR 0x03
#define DAY_ADDR 0x04
#define MONTH_ADDR 0x05
#define YEAR_ADDR 0x06
#define CONTROL_ADDR 0x07


// настройки SQ
#define _1HZ 0x90
#define _4096HZ 0x91
#define _8192HZ 0x92
#define _32768HZ 0x93

// функции
uint8_t ds1307_read_time_date(uint8_t *massiv); // чтение даты и времени из микросхемы в массив.
uint8_t ds1307_write_time(uint8_t hh, uint8_t mm);// запись времени hh -часы. mm -минуты.
uint8_t ds1307_write_date(uint8_t week, uint8_t day, uint8_t month, uint8_t year); // запись даты день недели, дата, мес€ц, год
uint8_t ds1307_clock_stop(uint8_t onoff);// onoff=1/0 остановка/запуск часов
uint8_t ds1307_sq(uint8_t byte); // настройка выхода SQ

// вспомогайки
uint8_t bcd2dec(uint8_t val);// конверт BCD в дес€тичное
uint8_t dec2bcd(uint8_t val);// конверт дес€тичное в BCD 

#endif /* DS1307_H_ */