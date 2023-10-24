#include "MKL25Z4.h"                    // Device header
#include "pwm.h"

void stopMotors(void) {
	TPM0_C1V = 0;
	TPM0_C2V = 0;
	TPM2_C0V = 0;
	TPM2_C1V = 0;
}

void moveForward(void) {
	TPM0_C1V = 3750;
	TPM0_C2V = 3750;
	TPM2_C0V = 3750;
	TPM2_C1V = 3750;
}

void rotateLeft(void) {
	TPM0_C1V = 3750;
	TPM0_C2V = 0;
	TPM2_C0V = 3750;
	TPM2_C1V = 0;
}

void rotateRight(void) {
	TPM0_C1V = 0;
	TPM0_C2V = 3750;
	TPM2_C0V = 0;
	TPM2_C1V = 3750;
}

void forwardLeft(void) {
	TPM0_C1V = 3750;
	TPM0_C2V = 1500;
	TPM2_C0V = 3750;
	TPM2_C1V = 1500;
}

void forwardRight(void) {
	TPM0_C1V = 1500;
	TPM0_C2V = 3750;
	TPM2_C0V = 1500;
	TPM2_C1V = 3750;
}

void moveBackward(void) {
	TPM0_C1V = 0;
	TPM0_C2V = 0;
	TPM2_C0V = 0;
	TPM2_C1V = 0;
	TPM0_C3V = 3750;
	TPM0_C4V = 3750;
}