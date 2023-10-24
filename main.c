/*----------------------------------------------------------------------------
 * CMSIS-RTOS 'main' function template
 *---------------------------------------------------------------------------*/
 
#include "RTE_Components.h"
#include  CMSIS_device_header
#include "cmsis_os2.h"
#include "queue.h"

#define BAUD_RATE 9600
 
/*----------------------------------------------------------------------------
 * Application main thread
 *---------------------------------------------------------------------------*/
void initUART1(uint32_t baud_rate) {
	uint32_t divisor, bus_clock;
	
	SIM->SCGC4 |= SIM_SCGC4_UART2_MASK;
	SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK;
	
	PORTA->PCR[18] &= ~PORT_PCR_MUX_MASK;
	PORTA->PCR[18] |= PORT_PCR_MUX(3);
	
	PORTA->PCR[19] &= ~PORT_PCR_MUX_MASK;
	PORTA->PCR[19] |= PORT_PCR_MUX(3);
	
	
	UART1->C2 &= ~((UART_C2_TE_MASK) | (UART_C2_RE_MASK));
	
	bus_clock = (DEFAULT_SYSTEM_CLOCK)/2;
	divisor = bus_clock / (baud_rate * 16);
	UART1->BDH = UART_BDH_SBR(divisor >> 8);
	UART1->BDL = UART_BDL_SBR(divisor);
	
	UART1->C1 = 0;
	UART1->S2 = 0;
	UART1->C3 = 0;
	
	NVIC_SetPriority(UART1_IRQn, 128);
	NVIC_ClearPendingIRQ(UART1_IRQn);
	NVIC_EnableIRQ(UART1_IRQn);
	
	UART1->C2 |= ((UART_C2_TE_MASK) | (UART_C2_RE_MASK));
	Q_Init(&tx_q);
	Q_Init(&rx_q);
}

void UART1_IRQHandler(void) {
	NVIC_ClearPendingIRQ(UART1_IRQn);
	// TX
	if (UART1->S1 & UART_S1_TDRE_MASK) {
		if (!Q_Empty(&tx_q)) {
			UART1->D =  Q_Dequeue(&tx_q);
		} else {
			UART1->C2 &= ~UART_C2_TE_MASK;
		}
	}
	// RX
	if (UART1->S1 & UART_S1_RDRF_MASK) {
		if (!Q_Full(&rx_q)) {
			Q_Enqueue(&rx_q, UART1->D);
		}
	}
	// error
	if (UART1->S1 & (UART_S1_OR_MASK | UART_S1_NF_MASK | UART_S1_FE_MASK | UART_S1_PF_MASK)) {
		unsigned char foo;
		foo = UART1->D;
	}
}

void commandHandler(Q_T *q) {
	unsigned char cmd = Q_Dequeue(q);
	//buzzer commands
	if ((cmd & 0x10) == 0x10) {
		// music on
	} 
	else if ((cmd & 0x20) == 0x20) {
		// end race
	} 
	else if ((cmd | 0xcf) == 0xaf) {
		// music off
	}
	
	//motor commands
	if ((cmd & 0x0a) == 0x0a) {
		// forward left
	}
	else if ((cmd & 0x06) == 0x06) {
		// forward right
	}
	else if ((cmd & 0x01) == 0x01) {
		// backward
	}
	else if ((cmd & 0x08) == 0x08) {
		// left
	}
	else if ((cmd & 0x04) == 0x04) {
		// right
	} 
	else if ((cmd & 0x02) == 0x02) {
		// forward
	}
}

void app_main (void *argument) {
 
  // ...
  for (;;) {}
}
 
int main (void) {
 
  // System Initialization
  SystemCoreClockUpdate();
  // ...
	initUART1(BAUD_RATE);
 
  osKernelInitialize();                 // Initialize CMSIS-RTOS
  osThreadNew(app_main, NULL, NULL);    // Create application main thread
  osKernelStart();                      // Start thread execution
  for (;;) {}
}
