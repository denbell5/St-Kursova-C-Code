/*
 * TC74.h
 *
 * Created: 3/26/2020 2:49:19 PM
 *  Author: denbe
 */ 


#ifndef TC74_H_
#define TC74_H_

#define TC74_READ  0b10011011
#define TC74_WRITE 0b10011010
#define TC74_DATA_READY 0b01000000

void TC74_write(uint8_t data);
uint8_t TC74_read();
bool TC74_IsReady();
#endif /* TC74_H_ */