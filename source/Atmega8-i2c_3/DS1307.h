#ifndef DS1307_H_
#define DS1307_H_

#define DS1307_WRITE 0b11010000 // ����� ��� ������
#define DS1307_READ 0b11010001 // ����� ��� ������ 

// ������ ���������
#define SEC_ADDR 0x00
#define MIN_ADRR 0x01
#define HOUR_ADDR 0x02
#define WEEK_ADDR 0x03
#define DAY_ADDR 0x04
#define MONTH_ADDR 0x05
#define YEAR_ADDR 0x06
#define CONTROL_ADDR 0x07


// ��������� SQ
#define _1HZ 0x90
#define _4096HZ 0x91
#define _8192HZ 0x92
#define _32768HZ 0x93

// �������
uint8_t ds1307_read_time_date(uint8_t *massiv); // ������ ���� � ������� �� ���������� � ������.
uint8_t ds1307_write_time(uint8_t hh, uint8_t mm);// ������ ������� hh -����. mm -������.
uint8_t ds1307_write_date(uint8_t week, uint8_t day, uint8_t month, uint8_t year); // ������ ���� ���� ������, ����, �����, ���
uint8_t ds1307_clock_stop(uint8_t onoff);// onoff=1/0 ���������/������ �����
uint8_t ds1307_sq(uint8_t byte); // ��������� ������ SQ

// �����������
uint8_t bcd2dec(uint8_t val);// ������� BCD � ����������
uint8_t dec2bcd(uint8_t val);// ������� ���������� � BCD 

#endif /* DS1307_H_ */