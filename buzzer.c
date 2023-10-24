#include "MKL25Z4.h"                    // Device header

#include "RTE_Components.h"
#include  CMSIS_device_header
#include "cmsis_os2.h"
#include "colorHandler.h"

#define MASK(x) (1 << (x))
int volatile modValue = 0;
int volatile cnvValue = 0;

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
	cnvValue = modValue / 2;
}

void changeFrequency(int frequency) {
	calculateModValue(frequency);
	calculateCnvValue();
	TPM1->MOD = modValue;
	TPM1_C0V = cnvValue;
}