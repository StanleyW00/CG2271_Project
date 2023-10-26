#define BUZZER_H
#include "MKL25Z4.h"                    // Device header

void initBuzzerPWM(void);
void calculateModValue(int frequency);
void calculateCnvValue(void);
void changeFrequency(int frequency);
void runningBuzzer(void);
void endBuzzer(void);
