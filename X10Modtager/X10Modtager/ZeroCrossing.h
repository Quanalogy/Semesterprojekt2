#ifndef ZEROCROSSING_H_
#define ZEROCROSSING_H_

#include "GlobalInclude.h"

void zeroCrossInit();

void activateZeroCrossInterrupt();
void deactivateZeroCrossInterrupt();

ISR(INT4_vect);

#endif /* ZEROCROSSING_H_ */