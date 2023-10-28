#include "MKL25Z4.h"                    // Device header
#include "pwm.h"

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
	TPM0_C4V = 7000;
	TPM0_C1V = 7000;
	TPM0_C2V = 0;
	//TPM2_C0V = 0;
	//TPM2_C1V = 0;
}

void rotateLeft(void) {
	TPM0_C1V = 5500;
	TPM0_C2V = 0;
	TPM0_C3V = 5500;
	TPM0_C4V = 0;
	//TPM2_C0V = 5000;
	//TPM2_C1V = 5000;
}

void rotateRight(void) {
	TPM0_C1V = 0;
	TPM0_C2V = 5500;
	TPM0_C3V = 0;
	TPM0_C4V = 5500;
	//TPM2_C0V = 3750;
	//TPM2_C1V = 3750;
}

void forwardLeft(void) {
	TPM0_C1V = 6500;
	TPM0_C2V = 0;
	TPM0_C3V = 0;
	TPM0_C4V = 0;
	//TPM2_C0V = 3750;
	//TPM2_C1V = 3750;
}

void forwardRight(void) {
	TPM0_C1V = 0;
	TPM0_C2V = 0;
	TPM0_C3V = 0;
	TPM0_C4V = 6500;
	//TPM2_C0V = 3750;
	//TPM2_C1V = 3750;
}

void moveBackward(void) {
	TPM0_C1V = 0;
	TPM0_C2V = 6000;
	TPM0_C3V = 6000;
	TPM0_C4V = 0;
	//TPM2_C0V = 3750; //BR
	//TPM2_C1V = 3750; //BL
}                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                 
