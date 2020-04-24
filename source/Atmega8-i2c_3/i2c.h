#ifndef I2C_H_
#define I2C_H_

#define I2C_SPEED 10000 // частота шины и2с


// статусные коды
#define TWI_START                  0x08  // старт был отправлен
#define TWI_REP_START              0x10  // повторный старт был отправлен
#define TWI_ARB_LOST               0x38  // потеря приоритета, шина занята

// Статусные коды ведущего передатчика MTX
#define TWI_MTX_ADR_ACK            0x18  // передан адрес записи-SLA+W и был получен ответ/подтверждение - ACK
#define TWI_MTX_ADR_NACK           0x20  // передан адрес записи-SLA+W без подтверждения - NACK 
#define TWI_MTX_DATA_ACK           0x28  // передан байт и полученно подтверждение - ACK
#define TWI_MTX_DATA_NACK          0x30  // передан байт без подтверждения - NACK 

// Статусные коды ведущего приемника MRX
#define TWI_MRX_ADR_ACK            0x40  // передан адрес записи-SLA+R и получен ответ подтвержение - ACK 
#define TWI_MRX_ADR_NACK           0x48  // Sпередан адрес записи-SLA+R без пдтверждения - NACK
#define TWI_MRX_DATA_ACK           0x50  // получен байт  и отправленно подверждение ведомому - ACK
#define TWI_MRX_DATA_NACK          0x58  // получен байт без подверждение ведомому - NACK 

//пользовательские коды
#define TWI_OK                0xff // без ошибок
#define TWSR_MASK          0xf8 // маска 

void i2c_init(void); // настройка частоты шины и2с
void i2c_wait(void); // ожидание
uint8_t i2c_start(void); // старт
void i2c_stop(void); // стоп
uint8_t i2c_send_addr(uint8_t address); // отправка адреса
uint8_t i2c_send_byte(uint8_t byte); // отправка байта
uint8_t i2c_read_byte(uint8_t *byte, uint8_t ack); // чтение байта. ack=0/1 - NACK/ACK

unsigned char i2c_readAck(void);
unsigned char i2c_readNak(void);

#endif /* I2C_H_ */