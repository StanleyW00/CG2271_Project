/*----------------------------------------------------------------------------
 * CMSIS-RTOS 'main' function template
 *---------------------------------------------------------------------------*/
 
#include "RTE_Components.h"
#include  CMSIS_device_header
#include "cmsis_os2.h"
#include "colorHandler.h"
 
#define MASK(x) (1 << (x))
int volatile modValue = 0;
int volatile cnvValue = 0;

#define PTB0_Pin 0
#define PTB1_Pin 1
#define PTB2_Pin 2
#define PTB3_Pin 3
#define TPM_1 1
#define TPM_2 2

int volatile modValue1 = 7500;
int volatile modValue2 = 7500;
int volatile cnvValue1 = 3000;
int volatile cnvValue2 = 3000;


/*----------------------------------------------------------------------------
 * Application main thread
 *---------------------------------------------------------------------------*/
void movingGreenLED (void *argument) {

  for (;;) {
		startMovingGreen();
	}
}

void stationGreenLED (void *argument) {
	
	 for (;;) {
		startStationGreen();
	}
}

void movingRedLED (void *argument) {
	 for (;;) {
		 startSlowFlashRed();
	 }
}

void stationRedLED (void *argument) {
	 for (;;) {
		 startFastFlashRed();
	 }
}


void initBuzzerPWM(void) {
	SIM_SCGC5 |= SIM_SCGC5_PORTC_MASK;
	
	PORTC->PCR[2] &= ~PORT_PCR_MUX_MASK;
	PORTC->PCR[2] |= PORT_PCR_MUX(4);
	
	SIM->SCGC6 |= SIM_SCGC6_TPM0_MASK;
	
	SIM->SOPT2 &= ~SIM_SOPT2_TPMSRC_MASK;
	SIM->SOPT2 |= SIM_SOPT2_TPMSRC(1);
	
	TPM0->MOD = 7500;
	
	TPM0->SC &= ~((TPM_SC_CMOD_MASK) | (TPM_SC_PS_MASK));
	TPM0->SC |= (TPM_SC_CMOD(1) | TPM_SC_PS(7));
	TPM0->SC &= ~(TPM_SC_CPWMS_MASK);
	
	TPM0_C1SC &= ~((TPM_CnSC_ELSB_MASK) | (TPM_CnSC_ELSA_MASK) | (TPM_CnSC_MSB_MASK) | (TPM_CnSC_MSA_MASK));
	TPM0_C1SC |= (TPM_CnSC_ELSB(1) | TPM_CnSC_MSB(1));
}


void calculateModValue(int frequency) {
	modValue = (375000 / frequency);
}

void calculateCnvValue() {
	// dutyCycle
	cnvValue = (modValue)/10;
}

void changeFrequency(int frequency) {
	calculateModValue(frequency);
	calculateCnvValue();
	TPM0->MOD = modValue;
	TPM0_C1V = cnvValue;
}

void controlBuzzer(void *argument) {
	
	/*
	 for (;;) {
		changeFrequency(524); // c
		osDelay(1000);
		changeFrequency(588); // d
		osDelay(1000);
		changeFrequency(660); // e
		osDelay(1000);	
		changeFrequency(698); // f
		osDelay(1000);		
		changeFrequency(784); // g
		osDelay(1000);
		changeFrequency(880); // a
		osDelay(1000);
		changeFrequency(988); // b
		osDelay(1000);
	 }
	*/
	
	/*
	for (;;) {
		changeFrequency(1482); // e
		osDelay(2000);
		changeFrequency(1321); // d
		osDelay(1000);
		changeFrequency(1976); // a
		osDelay(3000);
		changeFrequency(1482); // e
		osDelay(1000);
		changeFrequency(1321); // d
		osDelay(1000);
		changeFrequency(1760); // g
		osDelay(2000);
		changeFrequency(1567); // f
		osDelay(1000);
		changeFrequency(1482); // e
		osDelay(3000);
	}
	*/
	
	//run mode
	for (;;) {
		changeFrequency(880); // g
		osDelay(1000);
		changeFrequency(988); // a
		osDelay(1000);
		changeFrequency(1109); // b
		osDelay(1000);
		changeFrequency(1176); // c
		osDelay(1000);
		changeFrequency(880); // g
		osDelay(1000);
		changeFrequency(988); // a
		osDelay(1000);
		changeFrequency(1109); // b
		osDelay(1000);
		changeFrequency(1320); // d
		osDelay(1000);
		changeFrequency(1176); // c
		osDelay(1000);
		changeFrequency(1109); // b
		osDelay(1000);
		changeFrequency(1176); // c
		osDelay(1000);
		changeFrequency(1320); // d
		osDelay(1000);
		changeFrequency(880); // g
		osDelay(4000);
	}
}

int main (void) {
 
  // System Initialization
  SystemCoreClockUpdate();
  //initGPIOLED();
	initBuzzerPWM();
	
	TPM0_C1V = 0;
 
  osKernelInitialize();                 // Initialize CMSIS-RTOS
  osThreadNew(controlBuzzer, NULL, NULL);    // Create application main thread
  osKernelStart();                      // Start thread execution
  for (;;) {}
}
