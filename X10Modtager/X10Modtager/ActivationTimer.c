#include "ActivationTimer.h"
#include "Light.h"


void activationTimerInit()
{
	lightInit();

	TCCR3A = (TCCR3A & 0b11111100);		// Normal mode v�lges
	TCCR3B = (TCCR3B & 0b11100111);		//

	activationTimerStop();

	activationClokcReset();

	TIMSK3 = (TIMSK3 | 0b00000001);		// Interrupt enable
	sei();								//
}


void activationTimerStart()
{
	activationTimerReset();
	TCCR3B = (TCCR3B | 0b00000101);		// Preescaler s�ttes til 1024
	TCCR3B = (TCCR3B & 0b11111101);		//
}


void activationTimerStop()
{
	TCCR3B = (TCCR3B & 0b11111000);		// Preescaler s�ttes til 0
}


void activationTimerReset()
{
	waitedTime = 0;						// Timeren resetes
}


void activationClokcReset()
{
	TCNT3 = SEC_TIME;					// T�lleregister s�ttes til 49911 = 1 sek delay
}


ISR(TIMER3_OVF_vect)					// Interrupt hvert sekund
{
	waitedTime++;						

	if (waitedTime >= PIR_WAIT_TIME)	
	{
		setLightLevel(0);				
		waitedTime = 0;
		activationTimerStop();
	}
	else
	{
		setLightLevel(100);
	}

	activationClokcReset();
}