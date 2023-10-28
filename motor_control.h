#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H

#include "MKL25Z4.h"

void stopMotors(void);
void moveForward(void);
void rotateLeft(void);
void rotateRight(void);
void forwardLeft(void);
void forwardRight(void);
void moveBackward(void);

void stopMotors(void) {
	TPM0_C1V = 0;
	TPM0_C2V = 0;
	//TPM2_C0V = 0;
	//TPM2_C1V = 0;
	TPM0_C3V = 0;
	TPM0_C4V = 0;
}

void moveForward(void) {
	TPM0_C3V = 0;
	TPM0_C4V = 0;
	TPM0_C1V = 3750;
	TPM0_C2V = 3750;
	//TPM2_C0V = 0;
	//TPM2_C1V = 0;
}

void rotateLeft(void) {
	TPM0_C1V = 3750;
	TPM0_C2V = 0;
	TPM0_C3V = 3750;
	TPM0_C4V = 0;
	//TPM2_C0V = 3750;
	//TPM2_C1V = 3750;
}

void rotateRight(void) {
	TPM0_C1V = 0;
	TPM0_C2V = 3750;
	TPM0_C3V = 0;
	TPM0_C4V = 3750;
	//TPM2_C0V = 3750;
	//TPM2_C1V = 3750;
}

void forwardLeft(void) {
	TPM0_C1V = 3750;
	TPM0_C2V = 0;
	TPM0_C3V = 0;
	TPM0_C4V = 0;
	//TPM2_C0V = 3750;
	//TPM2_C1V = 3750;
}

void forwardRight(void) {
	TPM0_C1V = 0;
	TPM0_C2V = 3750;
	TPM0_C3V = 0;
	TPM0_C4V = 0;
	//TPM2_C0V = 3750;
	//TPM2_C1V = 3750;
}

void moveBackward(void) {
	TPM0_C1V = 0;
	TPM0_C2V = 0;
	TPM0_C3V = 3750;
	TPM0_C4V = 3750;
	//TPM2_C0V = 3750; //BR
	//TPM2_C1V = 3750; //BL
}                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                 

#endif
