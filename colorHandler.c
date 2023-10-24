#include "MKL25Z4.h"    
#include "colorHandler.h"
#include "RTE_Components.h"
#include  CMSIS_device_header
#include "cmsis_os2.h"

#define MASK(x) (1 << (x))

void initGPIOLED(void) {
		SIM->SCGC5 |= (SIM_SCGC5_PORTD_MASK) | (SIM_SCGC5_PORTE_MASK);
	
		//Green LED
		PORTD->PCR[0] &= ~PORT_PCR_MUX_MASK;
		PORTD->PCR[0] |= PORT_PCR_MUX(1);
		PORTD->PCR[1] &= ~PORT_PCR_MUX_MASK;
		PORTD->PCR[1] |= PORT_PCR_MUX(1);
		PORTD->PCR[2] &= ~PORT_PCR_MUX_MASK;
		PORTD->PCR[2] |= PORT_PCR_MUX(1);
		PORTD->PCR[3] &= ~PORT_PCR_MUX_MASK;
		PORTD->PCR[3] |= PORT_PCR_MUX(1);
		PORTD->PCR[4] &= ~PORT_PCR_MUX_MASK;
		PORTD->PCR[4] |= PORT_PCR_MUX(1);
		PORTD->PCR[5] &= ~PORT_PCR_MUX_MASK;
		PORTD->PCR[5] |= PORT_PCR_MUX(1);
		PORTD->PCR[6] &= ~PORT_PCR_MUX_MASK;
		PORTD->PCR[6] |= PORT_PCR_MUX(1);
		PORTD->PCR[7] &= ~PORT_PCR_MUX_MASK;
		PORTD->PCR[7] |= PORT_PCR_MUX(1);
		
		//Red LED
		PORTE->PCR[0] &= ~PORT_PCR_MUX_MASK;
		PORTE->PCR[0] |= PORT_PCR_MUX(1);
		PORTE->PCR[1] &= ~PORT_PCR_MUX_MASK;
		PORTE->PCR[1] |= PORT_PCR_MUX(1);
		PORTE->PCR[2] &= ~PORT_PCR_MUX_MASK;
		PORTE->PCR[2] |= PORT_PCR_MUX(1);
		PORTE->PCR[3] &= ~PORT_PCR_MUX_MASK;
		PORTE->PCR[3] |= PORT_PCR_MUX(1);
		PORTE->PCR[4] &= ~PORT_PCR_MUX_MASK;
		PORTE->PCR[4] |= PORT_PCR_MUX(1);
		PORTE->PCR[5] &= ~PORT_PCR_MUX_MASK;
		PORTE->PCR[5] |= PORT_PCR_MUX(1);
		PORTE->PCR[20] &= ~PORT_PCR_MUX_MASK;
		PORTE->PCR[20] |= PORT_PCR_MUX(1);
		PORTE->PCR[21] &= ~PORT_PCR_MUX_MASK;
		PORTE->PCR[21] |= PORT_PCR_MUX(1);
	
		PTD->PDDR |= MASK(0) | MASK(1) | MASK(2) | MASK(3) | MASK(4) | MASK(5) | MASK (6) | MASK(7);
		PTE->PDDR |= MASK(0) | MASK(1) | MASK(2) | MASK(3) | MASK(4) | MASK(5) | MASK (20) | MASK(21);
}

void startMovingGreen(void) {
		PTD->PDOR = MASK(0);
		osDelay(100);
		PTD->PDOR = MASK(1);
		osDelay(100);
		PTD->PDOR = MASK(2);
		osDelay(100);
		PTD->PDOR = MASK(3);
		osDelay(100);
		PTD->PDOR = MASK(4);
		osDelay(100);
		PTD->PDOR = MASK(5);
		osDelay(100);
		PTD->PDOR = MASK(6);
		osDelay(100);
		PTD->PDOR = MASK(7);
		osDelay(100);
}

void startStationGreen(void) {
		PTD->PDOR |= MASK(0) | MASK(1) | MASK(2) | MASK(3) | MASK(4) | MASK(5) | MASK (6) | MASK(7);
}

void startSlowFlashRed(void) {
		PTE->PDOR |= MASK(0) | MASK(1) | MASK(2) | MASK(3) | MASK(4) | MASK(5) | MASK (20) | MASK(21);
		osDelay(500);
		PTE->PDOR = 0;
		osDelay(500);
}

void startFastFlashRed(void) {
		PTE->PDOR |= MASK(0) | MASK(1) | MASK(2) | MASK(3) | MASK(4) | MASK(5) | MASK (20) | MASK(21);
		osDelay(250);
		PTE->PDOR = 0;
		osDelay(250);
}
