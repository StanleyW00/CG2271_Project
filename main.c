/*----------------------------------------------------------------------------
 * CMSIS-RTOS 'main' function template
 *---------------------------------------------------------------------------*/
 
#include "RTE_Components.h"
#include  CMSIS_device_header
#include "cmsis_os2.h"

#include "MKL25Z4.h"                    // Device header
#include "pwm.h"
#include "motor_handler.h"
#include "colorHandler.h"
#include "buzzer.h"
#include "serial.h"

#define MASK(x) (1 << (x))
#define BLUE_LED 1 // PortD Pin 1

osEventFlagsId_t movingGreenFlag;
osEventFlagsId_t movingRedFlag;
osEventFlagsId_t stationGreenFlag;
osEventFlagsId_t stationRedFlag;
osEventFlagsId_t buzzerEndFlag;
osEventFlagsId_t buzzerRunFlag;

osMutexId_t myMutex;

const osThreadAttr_t thread_attr = {
	.priority = osPriorityNormal1
};

/*----------------------------------------------------------------------------
 * Application main thread
 *---------------------------------------------------------------------------*/

volatile uint8_t receivedData;
 
void motorMovingFlagsSet() {
  osEventFlagsSet(movingGreenFlag, 0x0001);
  osEventFlagsSet(movingRedFlag, 0x0001);
	osEventFlagsSet(buzzerRunFlag, 0x0001);
  osEventFlagsClear(stationGreenFlag, 0x0001);
  osEventFlagsClear(stationRedFlag, 0x0001);
}

void motorStopFlagsSet() {
  osEventFlagsSet(stationGreenFlag, 0x0001);
  osEventFlagsSet(stationRedFlag, 0x0001);
	osEventFlagsSet(buzzerEndFlag, 0x0001);
  osEventFlagsClear(movingGreenFlag, 0x0001);
  osEventFlagsClear(movingRedFlag, 0x0001);
	osEventFlagsClear(buzzerRunFlag, 0x0001);
}

void UART2_IRQHandler(void)
{
	NVIC_ClearPendingIRQ(UART2_IRQn);
	// copy what is in register to data when register is full
	if (UART2->S1 & UART_S1_RDRF_MASK)
	{
		receivedData = UART2->D;
		osMutexRelease(myMutex);
	}

	PORTE->ISFR = 0xffffffff;
}

void main_loop (void *argument) {
	for (;;) {
		osMutexAcquire(myMutex, osWaitForever);
		if (receivedData == 0x02) {
			PTD->PDOR &= ~MASK(BLUE_LED); 
		} else {
			PTD->PDOR |= MASK(BLUE_LED);
		}
	}
}

void movingGreenLED (void *argument) {
  for (;;) {
    osEventFlagsWait(movingGreenFlag, 0x0001, osFlagsNoClear, osWaitForever);
		startMovingGreen();
	}
}

void stationGreenLED (void *argument) {
	 for (;;) {
    osEventFlagsWait(stationGreenFlag, 0x0001, osFlagsNoClear, osWaitForever);
		startStationGreen();
	}
}

void movingRedLED (void *argument) {
	 for (;;) {
    osEventFlagsWait(movingRedFlag, 0x0001, osFlagsNoClear, osWaitForever);
		startSlowFlashRed();
	}
}

void stationRedLED (void *argument) {
	for (;;) {
    osEventFlagsWait(stationRedFlag, 0x0001, osFlagsNoClear, osWaitForever);
		startFastFlashRed();
	}
}


void controlBuzzer (void *argument) {
	for (;;) {
		osEventFlagsWait(buzzerRunFlag, 0x0001, osFlagsNoClear, osWaitForever);
		runningBuzzer();
	}
}


void finishBuzzer (void *argument) {
	for (;;) {
		osEventFlagsWait(buzzerEndFlag, 0x0001, osFlagsNoClear, osWaitForever);
		endBuzzer();
	}
}

int main (void) {
	
  // System Initialization
  SystemCoreClockUpdate();

	initPWM();
	initGPIOLED();
	initBuzzerPWM();
	initSerial();
	
  osKernelInitialize();                 // Initialize CMSIS-RTOS
	
	// Creating the led event flags
  movingGreenFlag = osEventFlagsNew(NULL);
  movingRedFlag = osEventFlagsNew(NULL);
  stationGreenFlag = osEventFlagsNew(NULL);
  stationRedFlag = osEventFlagsNew(NULL);
	buzzerRunFlag = osEventFlagsNew(NULL);
	buzzerEndFlag = osEventFlagsNew(NULL);
	
	myMutex = osMutexNew(NULL);
  osThreadNew(main_loop, NULL, &thread_attr);    // Create application main thread
	//osThreadNew(movingGreenLED, NULL, NULL);
  //osThreadNew(movingRedLED, NULL, NULL);
  //osThreadNew(stationGreenLED, NULL, NULL);
  //osThreadNew(stationRedLED, NULL, NULL);
	//osThreadNew(controlBuzzer, NULL, NULL);    // Create application main thread
	//osThreadNew(finishBuzzer, NULL, NULL);
  osKernelStart();                      // Start thread execution
	
  for (;;) {}
}
