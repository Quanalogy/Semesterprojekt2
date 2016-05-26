#include "GlobalInclude.h"
#include "ActivitySim.h"
#include "Light.h"
#include <stdlib.h>
#include "uart.h"			// Debug

volatile int simulatedTime = 0;
int simTime;

void activitySimInit()			// Testet - Virker
{
	TCCR4A = (TCCR4A & 0b11111100);		// Normal mode v�lges
	TCCR4B = (TCCR4B & 0b11100111);		//

	TCCR4B = (TCCR4B & 0b11111000);		// Preescaler s�ttes til 0

	TCNT4 = SEC_TIME;					// T�lle register s�ttes til 49911 = 1 sek.

	TIMSK4 = (TIMSK4 | 0b00000001);		// Interrupt enable

	sei();
}


void activitySimStart()			// Testet - Virker
{
	TCCR4B = (TCCR4B | 0b00000101);		// Preescaler s�ttes til 1024
	TCCR4B = (TCCR4B & 0b11111101);		//
	simTime = generateNewSimTime();
	lightOn();
	activityClockReset();
}


void activitySimStop()			// Testet - Virker
{
	SendChar('S');
	TCCR4B = (TCCR4B & 0b11111000);		// Preescaler s�ttes til 0
	lightOff();
}


int generateNewSimTime()		// Testet - Virker
{
	return ((rand() % MAX_SIM_TIME + 1) + MIN_SIM_TIME);	// Husk at gang med 60 f�r at f� minuter!
}


void activityClockReset()		// Testet - Virker
{
	TCNT4 = SEC_TIME;
}


ISR(TIMER4_OVF_vect)			// Testet - Virker
{
	simulatedTime++;

	if (simulatedTime >= simTime)
	{
		lightInvert();
		simulatedTime = 0;
		simTime = generateNewSimTime();
	}

	activityClockReset();
}