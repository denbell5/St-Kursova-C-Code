/*
 * InternalEeprom.h
 *
 * Created: 3/24/2020 6:14:15 PM
 *  Author: denbe
 */ 


#ifndef INTERNALEEPROM_H_
#define INTERNALEEPROM_H_



void iEEPROM_write(uint16_t uiAddress, uint8_t ucData);
void iEEPROM_write16(uint16_t uiAddress, uint16_t ucData);
uint8_t iEEPROM_read(uint16_t uiAddress);
uint16_t iEEPROM_read16(uint16_t uiAddress);


#endif /* INTERNALEEPROM_H_ */