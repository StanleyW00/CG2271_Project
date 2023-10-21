/*----------------------------------------------------------------------------
 * CMSIS-RTOS 'main' function template
 *---------------------------------------------------------------------------*/
 
#include "RTE_Components.h"
#include  CMSIS_device_header
#include "cmsis_os2.h"

#include "MKL25Z4.h"                    // Device header
#include "pwm.h"
#include "motor_control.h"
#include "colorHandler.h"
#include "buzzer.h"

osThreadId_t tIdMovingGreen;
osThreadId_t tIdStationGreen;
osThreadId_t tIdMovingRed;
osThreadId_t tIdStationRed;


/*----------------------------------------------------------------------------
 * Application main thread
 *---------------------------------------------------------------------------*/
 
void motorThread (void *argument) {
 
  // ...
  for (;;) {
		moveForward();
		osDelay(1000);
		stopMotors();
		osDelay(1000);
	}
}

void buzzerThread (void *argument) {
	 for (;;) {
		changeBuzzerFrequency(262);
		osDelay(1000);
		changeBuzzerFrequency(294);
		osDelay(1000);
		changeBuzzerFrequency(330);
		osDelay(1000);	
		changeBuzzerFrequency(349);
		osDelay(1000);		
		changeBuzzerFrequency(392);
		osDelay(1000);
		changeBuzzerFrequency(440);
		osDelay(1000);
		changeBuzzerFrequency(494);
		osDelay(1000);
	 }
}



static void delay(volatile uint32_t nof) {
  while(nof!=0) {
    __asm("NOP");
    nof--;
  }
}

void movingGreenLED (void *argument) {
  for (;;) {
    osThreadFlagsWait(0x0001, osFlagsNoClear, osWaitForever);
		startMovingGreen();
	}
}

void stationGreenLED (void *argument) {
  osThreadFlagsSet(tIdStationGreen, 0x0001);
	 for (;;) {
    osThreadFlagsWait(0x0001, osFlagsNoClear, osWaitForever);
		startStationGreen();
	}
}

void movingRedLED (void *argument) {
	 for (;;) {
    osThreadFlagsWait(0x0001, osFlagsNoClear, osWaitForever);
		startSlowFlashRed();
	}
}

void stationRedLED (void *argument) {
  osThreadFlagsSet(tIdStationRed, 0x0001);
	for (;;) {
    osThreadFlagsWait(0x0001, osFlagsNoClear, osWaitForever);
		startFastFlashRed();
	}
}

int main (void) {
	
  // System Initialization
  SystemCoreClockUpdate();
  // ...
	initPWM();
	initGPIOLED();
	initBuzzerPWM();
	
	TPM1_C0V = 3750;
	/*
	TPM1_C0V = 3750;
	TPM1_C1V = 3750;
	TPM2_C0V = 3750;
	TPM2_C1V = 3750;
	
	delay(0xffffff);
	*/
	
  osKernelInitialize();                 // Initialize CMSIS-RTOS
  //osThreadNew(motorThread, NULL, NULL);    // Create application main thread
	osThreadNew(buzzerThread, NULL, NULL);
	//tIdMovingGreen = osThreadNew(movingGreenLED, NULL, NULL);
  //tIdMovingRed = osThreadNew(movingRedLED, NULL, NULL);
  //tIdStationRed = osThreadNew(stationRedLED, NULL, NULL);
  //tIdStationGreen = osThreadNew(stationGreenLED, NULL, NULL);
  osKernelStart();                      // Start thread execution
	
  for (;;) {}
}
