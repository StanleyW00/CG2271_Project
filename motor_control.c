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
