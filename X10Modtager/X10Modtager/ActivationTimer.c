#include "ActivationTimer.h"
#include "Light.h"

volatile int waitedTime = 0;

void activationTimerInit()
{
	TCCR3A = (TCCR3A & 0b11111100);		// Normal mode v�lges
	TCCR3B = (TCCR3B & 0b11100111);		//

	TCCR3B = (TCCR3B & 0b11111000);		// Preescaler s�ttes til 0

	TCNT3  = sec_time;					// T�lleregister s�ttes til 49911 = 1 sek delay

	TIMSK3 = (TIMSK3 | 0b00000001);		// Interrupt enable

	sei();

	lightInit();
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
	waitedTime = 0;
}


void activationClokcReset()
{
	TCNT3 = sec_time;
}


ISR(TIMER3_OVF_vect)
{
	waitedTime++;

	if (waitedTime >= wait_time)
	{
		setLightLevel(0);
		waitedTime = 0;
		activationTimerStop();
	}
	else
	{
		setLightLevel(100);
	}

	activationClokcReset();			// Reset af t�lleregister
}