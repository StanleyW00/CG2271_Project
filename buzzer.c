#include "MKL25Z4.h"                    // Device header

#include "RTE_Components.h"
#include  CMSIS_device_header
#include "cmsis_os2.h"

#define MASK(x) (1 << (x))
int volatile modValue = 0;
int volatile cnvValue = 0;

	/*
	 As reference, remember to times 1.1225 to the frequency every use
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
	 
	*/
	
void initBuzzerPWM(void) {
	SIM_SCGC5 |= SIM_SCGC5_PORTB_MASK;
	
	PORTB->PCR[0] &= ~PORT_PCR_MUX_MASK;
	PORTB->PCR[0] |= PORT_PCR_MUX(3);
	
	SIM->SCGC6 |= SIM_SCGC6_TPM1_MASK;
	
	SIM->SOPT2 &= ~SIM_SOPT2_TPMSRC_MASK;
	SIM->SOPT2 |= SIM_SOPT2_TPMSRC(1);
	
	TPM1->MOD = 7500;
	
	TPM1->SC &= ~((TPM_SC_CMOD_MASK) | (TPM_SC_PS_MASK));
	TPM1->SC |= (TPM_SC_CMOD(1) | TPM_SC_PS(7));
	TPM1->SC &= ~(TPM_SC_CPWMS_MASK);
	
	TPM1_C0SC &= ~((TPM_CnSC_ELSB_MASK) | (TPM_CnSC_ELSA_MASK) | (TPM_CnSC_MSB_MASK) | (TPM_CnSC_MSA_MASK));
	TPM1_C0SC |= (TPM_CnSC_ELSB(1) | TPM_CnSC_MSB(1));
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
	TPM1->MOD = modValue;
	TPM1_C0V = cnvValue;
}

void runningBuzzer() {
		osDelay(1000);
	//run mode - danny Minecraft
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
		osDelay(1000);
}

void endBuzzer() {
		TPM1_C0V = 0;
		osDelay(1000);
		changeFrequency(784); // f
		osDelay(1000);
		changeFrequency(880); // g
		osDelay(1000);
		changeFrequency(0);
		osDelay(10);
		changeFrequency(880); // g
		osDelay(1000);
		changeFrequency(988); // a
		osDelay(1000);
		
		changeFrequency(1760); // g 1 octave
		osDelay(100);
		changeFrequency(1567); // f
		osDelay(100);
		changeFrequency(1482); // e
		osDelay(250);
		
		changeFrequency(784); // f
		osDelay(1000);
		changeFrequency(880); // g
		osDelay(1000);
		changeFrequency(0);
		osDelay(10);
		changeFrequency(880); // g
		osDelay(1500);
		TPM1_C0V = 0;
}