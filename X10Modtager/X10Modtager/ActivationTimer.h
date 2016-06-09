#ifndef ACTIVATIONTIMER_H_
#define ACTIVATIONTIMER_H_

#include "GlobalInclude.h"

volatile int waitedTime;

void activationTimerInit();
void activationTimerStart();
void activationTimerStop();
void activationTimerReset();
void activationClokcReset();

ISR(TIMER3_COMPA_vect);

#endif /* ACTIVATIONTIMER_H_ */