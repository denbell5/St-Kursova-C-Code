/*
 * FCD1004.h
 *
 * Created: 3/14/2020 1:23:26 PM
 *  Author: denbe
 */ 
// h = 0.8
// min 23pf
// max 50pf

#ifndef FCD1004_H_
#define FCD1004_H_

#include "main.h"

#define FCD1004_WRITE 0b10100000
#define FCD1004_READ 0b10100001
#define MIN_CAPACITANCE 0x17; // 23 pF
#define MAX_CAPACITANCE 0x32; // 50 pF
#define CAPDAC 0b01011 * 3.125;
#define LEVEL_COEFFICIENT 0x64 / MAX_CAPACITANCE; // для перевода в проценты
uint8_t fcd_write16(uint8_t reg, uint16_t data);
uint8_t fcd_read16(uint8_t reg, uint8_t *MLSB);
uint16_t FDC1004_read(uint8_t reg);

#endif /* FCD1004_H_ */