#include "RTE_Components.h"
#include "MKL25Z4.h"
#include CMSIS_device_header
#include "cmsis_os2.h"
#include "led.h"
#include "uart.h"
#include "motor_control.h"
#include "pwm.h"

#define BAUD_RATE 9600

volatile static color_t color = RED;
volatile static uint8_t rx_data;

void UART1_IRQHandler(void) {
	NVIC_ClearPendingIRQ(UART1_IRQn);
	if (UART1->S1 & UART_S1_RDRF_MASK) {
		rx_data = UART1->D;
	}
}

void UART_led_control(void *argument) {
	for (;;){
		if ((rx_data & 0x0a) == 0x0a) {
			color = CYAN;
			forwardLeft();
		}
		else if ((rx_data & 0x06) == 0x06) {
			color = YELLOW;
			forwardRight();
		}
		else if ((rx_data & 0x02) == 0x02) {
			color = GREEN;
			moveForward();
		} 
		else if ((rx_data & 0x01) == 0x01) {
			color = BLUE;
			moveBackward();
		}
		else if ((rx_data & 0x08)) {
			color = MAGENTA;
			rotateLeft();
		} else if ((rx_data & 0x04)) {
			color = WHITE;
			rotateRight();
		}
		else {
			color = RED;
			stopMotors();
		}
		led_control(color);
	}
}

int main(void)
{
	SystemCoreClockUpdate();
	InitGPIO();
	InitUART1(BAUD_RATE);
	initPWM();
	led_control(OFF);
	osKernelInitialize();
	osThreadNew(UART_led_control, NULL, NULL);
	osKernelStart();
	for(;;){}
}
