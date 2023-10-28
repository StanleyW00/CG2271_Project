#ifndef LED_H
#define LED_H
#include "MKL25Z4.h"
#define RED_LED 18
#define GREEN_LED 19
#define BLUE_LED 1
#define MASK(x) (1 << (x))

typedef enum {
	RED, GREEN, BLUE, YELLOW, CYAN, MAGENTA, WHITE, OFF
} color_t;

void InitGPIO(void);
void led_control(color_t color);

void InitGPIO(void)
{

SIM->SCGC5 |= ((SIM_SCGC5_PORTB_MASK) | (SIM_SCGC5_PORTD_MASK));

PORTB->PCR[RED_LED] &= ~PORT_PCR_MUX_MASK;
PORTB->PCR[RED_LED] |= PORT_PCR_MUX(1);
PORTB->PCR[GREEN_LED] &= ~PORT_PCR_MUX_MASK;
PORTB->PCR[GREEN_LED] |= PORT_PCR_MUX(1);
PORTD->PCR[BLUE_LED] &= ~PORT_PCR_MUX_MASK;
PORTD->PCR[BLUE_LED] |= PORT_PCR_MUX(1);

PTB->PDDR |= (MASK(RED_LED) | MASK(GREEN_LED));
PTD->PDDR |= MASK(BLUE_LED);
}

void led_control(color_t color) {
	switch (color)
	{
		case RED:
			PTB->PDOR &= ~MASK(RED_LED);
			PTB->PDOR |= MASK(GREEN_LED);
			PTD->PDOR |= MASK(BLUE_LED);
			break;
		case GREEN:
			PTB->PDOR &= ~MASK(GREEN_LED);
			PTB->PDOR |= MASK(RED_LED);
			PTD->PDOR |= MASK(BLUE_LED);
			break;
		case BLUE:
			PTD->PDOR &= ~MASK(BLUE_LED);
			PTB->PDOR |= (MASK(RED_LED) | MASK(GREEN_LED));
			break;
		case CYAN:
			PTB->PDOR |= MASK(RED_LED);
			PTB->PDOR &= ~MASK(GREEN_LED);
			PTD->PDOR &= ~MASK(BLUE_LED);
			break;
		case YELLOW:
			PTD->PDOR |= MASK(BLUE_LED);
			PTB->PDOR &= ~(MASK(RED_LED) | MASK(BLUE_LED));
			break;
		case MAGENTA:
			PTB->PDOR &= ~MASK(RED_LED);
			PTB->PDOR |= MASK(GREEN_LED);
			PTD->PDOR &= ~MASK(BLUE_LED);
			break;
		case WHITE:
			PTB->PDOR &= ~(MASK(RED_LED) | MASK(GREEN_LED));
			PTD->PDOR &= ~MASK(BLUE_LED);
			break;
		case OFF:
			PTB->PDOR |= MASK(RED_LED) | MASK(GREEN_LED);
			PTD->PDOR |= MASK(BLUE_LED);
			break;
	}
}
#endif
