#include "GlobalInclude.h"
#include "ActivitySim.h"
#include "Light.h"
#include <stdlib.h>


void activitySimInit()
{
	lightInit();
	
	TCCR4A = (TCCR4A & 0b11111100);		// Normal mode vælges.
	TCCR4B = (TCCR4B & 0b11100111);		//

	activitySimStop();				

	activityClockReset();				// Tælle register sættes til 49911 = 1 sek.
	simulatedTime = 0;					// Tælleren resetes.

	TIMSK4 = (TIMSK4 | 0b00000001);		// Interrupt enable.
	sei();								//
}


void activitySimStart()
{
	TCCR4B = (TCCR4B | 0b00000101);		// Preescaler sættes til 1024.
	TCCR4B = (TCCR4B & 0b11111101);		//
	simTime = generateNewSimTime();
	lightOn();
	activityClockReset();
}


void activitySimStop()
{
	TCCR4B = (TCCR4B & 0b11111000);		// Preescaler sættes til 0.
	lightOff();
}


int activitySimCheckRunning()
{
	if ((TCCR4B & 0b00000111) == 0b00000101)	// Check om simuleringen kører.
		return 1;
	else
		return 0;
}


int generateNewSimTime()
{
	return ((rand() % MAX_SIM_TIME + 1) + MIN_SIM_TIME);	// Tilfældig tid beregnes.
															// Husk at gang med 60 for at få minuter!
}


int generateNewLightLevel()
{
	return ((rand() % MAX_SIM_LIGHT + 1) + MIN_SIM_LIGHT);
}


void activityClockReset()
{
	TCNT4 = SEC_TIME;										// Tælle register sættes til 49911 = 1 sek.
}


ISR(TIMER4_OVF_vect)
{
	simulatedTime++;

	if (simulatedTime >= simTime)
	{
		setLightLevel(generateNewLightLevel());
		lightInvert();
		simulatedTime = 0;
		simTime = generateNewSimTime();
	}

	activityClockReset();
}