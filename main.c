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


void initPWM(void) {
	SIM_SCGC5 |= SIM_SCGC5_PORTC_MASK;
	
	PORTC->PCR[1] &= ~PORT_PCR_MUX_MASK;
	PORTC->PCR[1] |= PORT_PCR_MUX(4);
	
	SIM->SCGC6 |= SIM_SCGC6_TPM0_MASK;
	
	SIM->SOPT2 &= ~SIM_SOPT2_TPMSRC_MASK;
	SIM->SOPT2 |= SIM_SOPT2_TPMSRC(1);
	
	TPM0->MOD = 7500;
	
	TPM0->SC &= ~((TPM_SC_CMOD_MASK) | (TPM_SC_PS_MASK));
	TPM0->SC |= (TPM_SC_CMOD(1) | TPM_SC_PS(7));
	TPM0->SC &= ~(TPM_SC_CPWMS_MASK);
	
	TPM0_C0SC &= ~((TPM_CnSC_ELSB_MASK) | (TPM_CnSC_ELSA_MASK) | (TPM_CnSC_MSB_MASK) | (TPM_CnSC_MSA_MASK));
	TPM0_C0SC |= (TPM_CnSC_ELSB(1) | TPM_CnSC_MSB(1));
}

void calculateModValue(int frequency) {
	modValue = (375000 / frequency);
}

void calculateCnvValue() {
	// dutyCycle
	cnvValue = modValue / 16;
}

void changeFrequency(int frequency) {
	calculateModValue(frequency);
	calculateCnvValue();
	TPM0->MOD = modValue;
	TPM0_C0V = cnvValue;
}

void controlBuzzer(void *argument) {
	 for (;;) {
		changeFrequency(262);
		osDelay(1000);
		changeFrequency(294);
		osDelay(1000);
		changeFrequency(330);
		osDelay(1000);	
		changeFrequency(349);
		osDelay(1000);		
		changeFrequency(392);
		osDelay(1000);
		changeFrequency(440);
		osDelay(1000);
		changeFrequency(494);
		osDelay(1000);
	 }
}

int main (void) {
 
  // System Initialization
  SystemCoreClockUpdate();
  //initGPIOLED();
	initPWM();
	
	TPM0_C0V = 3750;
 
  osKernelInitialize();                 // Initialize CMSIS-RTOS
  osThreadNew(controlBuzzer, NULL, NULL);    // Create application main thread
  osKernelStart();                      // Start thread execution
  for (;;) {}
}
