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

osMutexId_t myBuzzerMutex;

osEventFlagsId_t movingGreenFlag;
osEventFlagsId_t movingRedFlag;
osEventFlagsId_t stationGreenFlag;
osEventFlagsId_t stationRedFlag;

const osThreadAttr_t thread_attr = {
	.priority = osPriorityNormal1
};

/*----------------------------------------------------------------------------
 * Application main thread
 *---------------------------------------------------------------------------*/
 
void motorMovingFlagsSet() {
  osEventFlagsSet(movingGreenFlag, 0x0001);
  osEventFlagsSet(movingRedFlag, 0x0001);
  osEventFlagsClear(stationGreenFlag,0x0001);
  osEventFlagsClear(stationRedFlag,0x0001);
}

void motorStopFlagsSet() {
  osEventFlagsSet(stationGreenFlag, 0x0001);
  osEventFlagsSet(stationRedFlag, 0x0001);
  osEventFlagsClear(movingGreenFlag,0x0001);
  osEventFlagsClear(movingRedFlag,0x0001);
}

void motorThread (void *argument) {
  for (;;) {
    moveForward();
		//moveBackward();
    motorMovingFlagsSet();
    osDelay(2000);
    stopMotors();
    motorStopFlagsSet();
    osDelay(2000);
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


int main (void) {
	
  // System Initialization
  SystemCoreClockUpdate();
  // ...
	initPWM();
	initGPIOLED();
	
  osKernelInitialize();                 // Initialize CMSIS-RTOS
	
	
	// Creating the led event flags
  movingGreenFlag = osEventFlagsNew(NULL);
  movingRedFlag = osEventFlagsNew(NULL);
  stationGreenFlag = osEventFlagsNew(NULL);
  stationRedFlag = osEventFlagsNew(NULL);
	
  osThreadNew(motorThread, NULL, NULL);    // Create application main thread
	osThreadNew(movingGreenLED, NULL, NULL);
  osThreadNew(movingRedLED, NULL, NULL);
  osThreadNew(stationGreenLED, NULL, NULL);
  osThreadNew(stationRedLED, NULL, NULL);
	//osThreadNew(controlBuzzer, NULL, &thread_attr);    // Create application main thread
  osKernelStart();                      // Start thread execution
	
  for (;;) {}
}
