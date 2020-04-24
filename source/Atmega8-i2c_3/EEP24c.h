#ifndef EEP24C_H_
#define EEP24C_H_

#define EEP24C_WRITE 0b10101110 // запись
#define EEP24C_READ 0b10101111 // чтение


uint8_t eep_write_byte(uint16_t address,uint8_t byte); // запись байта
uint8_t eep_read_byte(uint16_t address, uint8_t *byte); // чтение байта
uint8_t eep_write_8massiv(uint16_t startaddress,uint8_t *massiv, uint8_t col); //запись 8 битного массива.
uint8_t eep_read_8massiv(uint16_t startaddress,uint8_t *massiv, uint8_t col); // чтение 8 битного массива.
#endif /* EEP24C_H_ */