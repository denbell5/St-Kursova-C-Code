/*
 * InternalEeprom.cpp
 *
 * Created: 3/24/2020 6:13:45 PM
 *  Author: denbe
 */ 
#include "main.h"

void iEEPROM_write(uint16_t uiAddress, uint8_t ucData)
{
	while(EECR & (1<<EEWE)) //���� ������������ ����� ��������� ��������� ��������� � �������
	{}
	EEAR = uiAddress; //������������� �����
	EEDR = ucData; //����� ������ � �������
	EECR |= (1<<EEMWE); //��������� ������
	EECR |= (1<<EEWE); //����� ���� � ������
}

void iEEPROM_write16(uint16_t uiAddress, uint16_t ucData)
{
	iEEPROM_write(uiAddress, (uint8_t)(ucData >> 8));
	iEEPROM_write(uiAddress+1, (uint8_t)ucData);	
}

uint8_t iEEPROM_read(uint16_t uiAddress)
{
	while(EECR & (1<<EEWE))
	{} //���� ������������ ����� ��������� ��������� ��������� � �������
	EEAR = uiAddress; //������������� �����
	EECR |= (1<<EERE); //��������� �������� ���������� �� ������ � ������� ������
	return EEDR; //���������� ���������
}

uint16_t iEEPROM_read16(uint16_t uiAddress)
{
	uint16_t data;
	data = iEEPROM_read(uiAddress);
	data = data << 8;
	data |= iEEPROM_read(uiAddress+1);
	
	return data;
}