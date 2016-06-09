#ifndef LIGHT_H_
#define LIGHT_H_

#include "GlobalInclude.h"

int lightLevel;

void lightInit();
void setLightLevel(int);	// int 0 - 100
void setPwmTimer(int);
void lightOn();
void lightOff();
void lightInvert();

#endif /* LIGHT_H_ */