#include "MKL25Z4.h"    
#include "colorHandler.h"
#include "RTE_Components.h"
#include  CMSIS_device_header
#include "cmsis_os2.h"

#define MASK(x) (1 << (x))

#define GREEN_0 0
#define GREEN_1 1
#define GREEN_2 2
#define GREEN_3 3
#define GREEN_4 4
#define GREEN_5 5
#define GREEN_6 6
#define GREEN_7 7

#define RED_0 0
#define RED_1 1
#define RED_2 2
#define RED_3 3
#define RED_4 4
#define RED_5 5
#define RED_6 20
#define RED_7 21


void initGPIOLED(void) {
		SIM->SCGC5 |= (SIM_SCGC5_PORTD_MASK) | (SIM_SCGC5_PORTE_MASK);
	
		//Green LED
		PORTD->PCR[GREEN_0] &= ~PORT_PCR_MUX_MASK;
		PORTD->PCR[GREEN_0] |= PORT_PCR_MUX(1);
		PORTD->PCR[GREEN_1] &= ~PORT_PCR_MUX_MASK;
		PORTD->PCR[GREEN_1] |= PORT_PCR_MUX(1);
		PORTD->PCR[GREEN_2] &= ~PORT_PCR_MUX_MASK;
		PORTD->PCR[GREEN_2] |= PORT_PCR_MUX(1);
		PORTD->PCR[GREEN_3] &= ~PORT_PCR_MUX_MASK;
		PORTD->PCR[GREEN_3] |= PORT_PCR_MUX(1);
		PORTD->PCR[GREEN_4] &= ~PORT_PCR_MUX_MASK;
		PORTD->PCR[GREEN_4] |= PORT_PCR_MUX(1);
		PORTD->PCR[GREEN_5] &= ~PORT_PCR_MUX_MASK;
		PORTD->PCR[GREEN_5] |= PORT_PCR_MUX(1);
		PORTD->PCR[GREEN_6] &= ~PORT_PCR_MUX_MASK;
		PORTD->PCR[GREEN_6] |= PORT_PCR_MUX(1);
		PORTD->PCR[GREEN_7] &= ~PORT_PCR_MUX_MASK;
		PORTD->PCR[GREEN_7] |= PORT_PCR_MUX(1);
		
		//Red LED
		PORTE->PCR[RED_0] &= ~PORT_PCR_MUX_MASK;
		PORTE->PCR[RED_0] |= PORT_PCR_MUX(1);
		PORTE->PCR[RED_1] &= ~PORT_PCR_MUX_MASK;
		PORTE->PCR[RED_1] |= PORT_PCR_MUX(1);
		PORTE->PCR[RED_2] &= ~PORT_PCR_MUX_MASK;
		PORTE->PCR[RED_2] |= PORT_PCR_MUX(1);
		PORTE->PCR[RED_3] &= ~PORT_PCR_MUX_MASK;
		PORTE->PCR[RED_3] |= PORT_PCR_MUX(1);
		PORTE->PCR[RED_4] &= ~PORT_PCR_MUX_MASK;
		PORTE->PCR[RED_4] |= PORT_PCR_MUX(1);
		PORTE->PCR[RED_5] &= ~PORT_PCR_MUX_MASK;
		PORTE->PCR[RED_5] |= PORT_PCR_MUX(1);
		PORTE->PCR[RED_6] &= ~PORT_PCR_MUX_MASK;
		PORTE->PCR[RED_6] |= PORT_PCR_MUX(1);
		PORTE->PCR[RED_7] &= ~PORT_PCR_MUX_MASK;
		PORTE->PCR[RED_7] |= PORT_PCR_MUX(1);
	
        // Turns on (?) all LEDs
		PTD->PDDR |= MASK(GREEN_0) | MASK(GREEN_1) | MASK(GREEN_2) | MASK(GREEN_3) | MASK(GREEN_4) | MASK(GREEN_5) | MASK (GREEN_6) | MASK(GREEN_7);
		PTE->PDDR |= MASK(RED_0) | MASK(RED_1) | MASK(RED_2) | MASK(RED_3) | MASK(RED_4) | MASK(RED_5) | MASK (RED_6) | MASK(RED_7);
}

void startMovingGreen(void) {
		PTD->PDOR = MASK(GREEN_0);
		osDelay(100);
		PTD->PDOR = MASK(GREEN_1);
		osDelay(100);
		PTD->PDOR = MASK(GREEN_2);
		osDelay(100);
		PTD->PDOR = MASK(GREEN_3);
		osDelay(100);
		PTD->PDOR = MASK(GREEN_4);
		osDelay(100);
		PTD->PDOR = MASK(GREEN_5);
		osDelay(100);
		PTD->PDOR = MASK(GREEN_6);
		osDelay(100);
		PTD->PDOR = MASK(GREEN_7);
		osDelay(100);
}

void startStationGreen(void) {
		PTD->PDOR |= MASK(GREEN_0) | MASK(GREEN_1) | MASK(GREEN_2) | MASK(GREEN_3) | MASK(GREEN_4) | MASK(GREEN_5) | MASK (GREEN_6) | MASK(GREEN_7);
}

void startSlowFlashRed(void) {
		PTE->PDOR |= MASK(RED_0) | MASK(RED_1) | MASK(RED_2) | MASK(RED_3) | MASK(RED_4) | MASK(RED_5) | MASK (RED_6) | MASK(RED_7);
		osDelay(500);
		PTE->PDOR = 0;
		osDelay(500);
}

void startFastFlashRed(void) {
		PTE->PDOR |= MASK(RED_0) | MASK(RED_1) | MASK(RED_2) | MASK(RED_3) | MASK(RED_4) | MASK(RED_5) | MASK (RED_6) | MASK(RED_7);
		osDelay(250);
		PTE->PDOR = 0;
		osDelay(250);
}
