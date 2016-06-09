#ifndef PIRSENSOR_H_
#define PIRSENSOR_H_

#include "GlobalInclude.h"

void pirInit();

int pirScan();

void pirInterruptStart();
void pirInterruptStop();
int pirInterruptCheckRunnig();		// 0 = notrunning, 1 = running

ISR(INT5_vect);

#endif /* PIRSENSOR_H_ */