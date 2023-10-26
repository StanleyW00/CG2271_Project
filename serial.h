#define SERIAL_H
#include "MKL25Z4.h"                    // Device header

#define BAUD_RATE 9600
#define UART_TX_PORTE22 22
#define UART_RX_PORTE23 23

void initSerial(void);
void init_UART_ISR(void);
