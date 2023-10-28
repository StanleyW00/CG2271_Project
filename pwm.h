#ifndef PWM_H
#define PWM_H

#include "MKL25Z4.h"  

void initPWM(void);
void stopMotors(void);
void moveForward(void);
void changeMotorFrequency(int frequency, int timer, int channel);

//TPM2
#define PTB2_Pin 2
#define PTB3_Pin 3

//TPM0
#define PTC2_Pin 2 //CH1
#define PTC3_Pin 3 //CH2
#define PTC4_Pin 4 //CH3
#define PTC8_Pin 8 //CH4

static int volatile modValue0 = 7500;
static int volatile modValue2 = 7500;
static int volatile cnvValue0 = 3000;
static int volatile cnvValue2 = 3000;

#define TPM_0 0
//#define TPM_1 1
#define TPM_2 2

#define LEFT_F 1
#define RIGHT_F 2

#define DUTY_CYCLE 16


void initPWM() {
	// Enable clock for PORTB
	SIM_SCGC5 |= SIM_SCGC5_PORTB_MASK;
	SIM_SCGC5 |= SIM_SCGC5_PORTC_MASK;
	
	// Configure MUX settings
	// /.PORTB->PCR[PTB0_Pin] &= ~PORT_PCR_MUX_MASK;
	//PORTB->PCR[PTB0_Pin] |= PORT_PCR_MUX(3);
	
	//PORTB->PCR[PTB1_Pin] &= ~PORT_PCR_MUX_MASK;
	//PORTB->PCR[PTB1_Pin] |= PORT_PCR_MUX(3);
	
	//PORTB->PCR[PTB2_Pin] &= ~PORT_PCR_MUX_MASK;
	//PORTB->PCR[PTB2_Pin] |= PORT_PCR_MUX(3);
	
	//PORTB->PCR[PTB3_Pin] &= ~PORT_PCR_MUX_MASK;
	//PORTB->PCR[PTB3_Pin] |= PORT_PCR_MUX(3);
	
	PORTC->PCR[PTC3_Pin] &= ~PORT_PCR_MUX_MASK;
	PORTC->PCR[PTC3_Pin] |= PORT_PCR_MUX(4);
	
	PORTC->PCR[PTC4_Pin] &= ~PORT_PCR_MUX_MASK;
	PORTC->PCR[PTC4_Pin] |= PORT_PCR_MUX(4);
	
	PORTC->PCR[PTC2_Pin] &= ~PORT_PCR_MUX_MASK;
	PORTC->PCR[PTC2_Pin] |= PORT_PCR_MUX(4);
	
	PORTC->PCR[PTC8_Pin] &= ~PORT_PCR_MUX_MASK;
	PORTC->PCR[PTC8_Pin] |= PORT_PCR_MUX(3);
	
	// Enable clock TPM2
	//SIM->SCGC6 |= SIM_SCGC6_TPM1_MASK;
	//SIM->SCGC6 |= SIM_SCGC6_TPM2_MASK;
	
	// Enable clock TPM0
	SIM->SCGC6 |= SIM_SCGC6_TPM0_MASK;
	
	// Select clock source for TPM counter clock
	SIM->SOPT2 &= ~SIM_SOPT2_TPMSRC_MASK;
	SIM->SOPT2 |= SIM_SOPT2_TPMSRC(1);
	
	TPM0->MOD = 7500;
	//TPM1->MOD = 7500;
	//TPM2->MOD = 7500;
	
	TPM0->SC &= ~((TPM_SC_CMOD_MASK) | (TPM_SC_PS_MASK));
	TPM0->SC |= (TPM_SC_CMOD(1) | TPM_SC_PS(7));
	TPM0->SC &= ~(TPM_SC_CPWMS_MASK);
	
	//TPM1->SC &= ~((TPM_SC_CMOD_MASK) | (TPM_SC_PS_MASK));
	//TPM1->SC |= (TPM_SC_CMOD(1) | TPM_SC_PS(7));
	//TPM1->SC &= ~(TPM_SC_CPWMS_MASK);
	
	//TPM2->SC &= ~((TPM_SC_CMOD_MASK) | (TPM_SC_PS_MASK));
	//TPM2->SC |= (TPM_SC_CMOD(1) | (TPM_SC_PS(7)));
	//TPM2->SC &= ~(TPM_SC_CPWMS_MASK);
	
	TPM0_C1SC &= ~((TPM_CnSC_ELSB_MASK) | (TPM_CnSC_ELSA_MASK) | (TPM_CnSC_MSB_MASK) | (TPM_CnSC_MSA_MASK));
	TPM0_C1SC |= (TPM_CnSC_ELSB(1) | TPM_CnSC_MSB(1));
	
	TPM0_C2SC &= ~((TPM_CnSC_ELSB_MASK) | (TPM_CnSC_ELSA_MASK) | (TPM_CnSC_MSB_MASK) | (TPM_CnSC_MSA_MASK));
	TPM0_C2SC |= (TPM_CnSC_ELSB(1) | TPM_CnSC_MSB(1));
	
	
	TPM0_C3SC &= ~((TPM_CnSC_ELSB_MASK) | (TPM_CnSC_ELSA_MASK) | (TPM_CnSC_MSB_MASK) | (TPM_CnSC_MSA_MASK));
	TPM0_C3SC |= (TPM_CnSC_ELSB(1) | TPM_CnSC_MSB(1));
	
	TPM0_C4SC &= ~((TPM_CnSC_ELSB_MASK) | (TPM_CnSC_ELSA_MASK) | (TPM_CnSC_MSB_MASK) | (TPM_CnSC_MSA_MASK));
	TPM0_C4SC |= (TPM_CnSC_ELSB(1) | TPM_CnSC_MSB(1));
	
	
	//TPM1_C0SC &= ~((TPM_CnSC_ELSB_MASK) | (TPM_CnSC_ELSA_MASK) | (TPM_CnSC_MSB_MASK) | (TPM_CnSC_MSA_MASK));
	//TPM1_C0SC |= (TPM_CnSC_ELSB(1) | TPM_CnSC_MSB(1));
	
	//TPM1_C1SC &= ~((TPM_CnSC_ELSB_MASK) | (TPM_CnSC_ELSA_MASK) | (TPM_CnSC_MSB_MASK) | (TPM_CnSC_MSA_MASK));
	//TPM1_C1SC |= (TPM_CnSC_ELSB(1) | TPM_CnSC_MSB(1));
	
	//TPM2_C0SC &= ~((TPM_CnSC_ELSB_MASK) | (TPM_CnSC_ELSA_MASK) | (TPM_CnSC_MSB_MASK) | (TPM_CnSC_MSA_MASK));
	//TPM2_C0SC |= (TPM_CnSC_ELSB(1) | TPM_CnSC_MSB(1));
	
	//TPM2_C1SC &= ~((TPM_CnSC_ELSB_MASK) | (TPM_CnSC_ELSA_MASK) | (TPM_CnSC_MSB_MASK) | (TPM_CnSC_MSA_MASK));
	//TPM2_C1SC |= (TPM_CnSC_ELSB(1) | TPM_CnSC_MSB(1));
}

void changeMotorFrequency(int frequency, int timer, int channel) {
	uint32_t mod_val = 375000 / frequency;
	uint32_t cnv_val = mod_val / DUTY_CYCLE;
	
	if(timer == TPM_0) {
		TPM0->MOD = mod_val;
		
		if(channel == 1) {
			TPM0_C1V = cnv_val;
		} else if (channel == 2) {
			TPM0_C2V = cnv_val;
		} else if (channel == 3) {
			TPM0_C3V = cnv_val;
		} else if (channel == 4) {
			TPM0_C4V = cnv_val;
		}
	}/* else if (timer == TPM_2) {
		TPM2->MOD = mod_val;
		
		if(channel == 0) {
			TPM2_C0V = cnv_val;
		} else if (channel == 1) {
			TPM2_C1V = cnv_val;
		}
	} */
}
#endif
