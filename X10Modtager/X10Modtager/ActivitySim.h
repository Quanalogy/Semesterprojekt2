#ifndef ACTIVITYSIM_H_
#define ACTIVITYSIM_H_

#include "GlobalInclude.h"

volatile int simulatedTime;
int simTime;

void activitySimInit();
void activitySimStart();
void activitySimStop();
int activitySimCheckRunning();		// 0 = not running, 1 = running

int generateNewSimTime();

void activityClockReset();

ISR(TIMER4_OVF_vect);

#endif /* ACTIVITYSIM_H_ */