#include "MKL25Z4.h"                    // Device header
#include "pwm.h"

void stopMotors(void) {
	TPM1_C0V = 0;
	TPM1_C1V = 0;
	TPM2_C0V = 0;
	TPM2_C1V = 0;
}

void moveForward(void) {
	TPM1_C0V = 3750;
	TPM1_C1V = 3750;
	TPM2_C0V = 3750;
	TPM2_C1V = 3750;
}

void rotateLeft(void) {
	TPM1_C0V = 3750;
	TPM1_C1V = 0;
	TPM2_C0V = 3750;
	TPM2_C1V = 0;
}

void rotateRight(void) {
	TPM1_C0V = 0;
	TPM1_C1V = 3750;
	TPM2_C0V = 0;
	TPM2_C1V = 3750;
}

void forwardLeft(void) {
	TPM1_C0V = 3750;
	TPM1_C1V = 1500;
	TPM2_C0V = 3750;
	TPM2_C1V = 1500;
}

void forwardRight(void) {
	TPM1_C0V = 1500;
	TPM1_C1V = 3750;
	TPM2_C0V = 1500;
	TPM2_C1V = 3750;
}

void moveBackward(void) {
	TPM1_C0V = 0;
	TPM1_C1V = 0;
	TPM2_C0V = 0;
	TPM2_C1V = 0;
	TPM0_C2V = 3750;
	TPM0_C3V = 3750;
}