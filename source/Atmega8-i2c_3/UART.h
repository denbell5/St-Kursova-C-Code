#ifndef UART_H_
#define UART_H_

#define PRESCALL 16 // 16 (U2X = 0) или 8 если скорость двойная (U2X = 1).
#define BAUD 9600 // скорость
#define MYUBRR F_CPU/PRESCALL/BAUD-1 // расчет значения для регистра UBRR из даташита... 

void uart_init(uint16_t ubrr); // инит уарта
void uart_send_byte(uint8_t data); // отправка байта
void uart_send_str(uint8_t *s); // отправка символа
void uart_send_flashstr(const char *string); // отправка строки из флэш памяти
void uart_send_int(uint16_t c); // отправка инта
void uart_send_numstr(uint16_t num); // отправка десятичного числа строкой
void uart_send_numstrHEX(uint16_t num); // число в шестнадцетиричной системе строкой
void uart_send_entr(); // отправка символа перехода на новую строку
void uart_send_numstrHEX32(uint32_t num);
uint8_t uart_read_byte(void); // чтение байта

#endif /* UART_H_ */