
#define BUZZER_H
#include "MKL25Z4.h"                    // Device header

void initBuzzerPWM(void);
void calculateModValue(int frequency);
void calculateCnvValue();
void changeBuzzerFrequency(int frequency);
