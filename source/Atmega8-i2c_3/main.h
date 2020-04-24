#ifndef MAIN_H_
#define MAIN_H_

#define F_CPU 1000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/pgmspace.h>
#include <stdio.h>
#include <stdlib.h>

#include "i2c.h"
#include "EEP24c.h"
#include "DS1307.h"
#include "UART.h"
#include "FCD1004.h"
#include "InternalEeprom.h"
#include "TC74.h"

uint16_t CalculateCapacitance(uint16_t data1, uint16_t data2);
uint16_t IncludeTemperatureOffset(uint8_t temperature, uint16_t capacitance);
bool IsTemperatureNegative(uint8_t data);

void ResetEEP();

#endif /* MAIN_H_ */