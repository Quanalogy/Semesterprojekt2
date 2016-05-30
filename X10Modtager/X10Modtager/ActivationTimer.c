#include "ActivationTimer.h"
#include "Light.h"


void activationTimerInit()
{
	lightInit();

	TCCR3A = (TCCR3A & 0b11111100);		// Normal mode vælges
	TCCR3B = (TCCR3B & 0b11100111);		//

	activationTimerStop();

	activationClokcReset();

	TIMSK3 = (TIMSK3 | 0b00000001);		// Interrupt enable
	sei();								//
}


void activationTimerStart()
{
	activationTimerReset();				//
	TCCR3B = (TCCR3B | 0b00000101);		// Preescaler sættes til 1024
	TCCR3B = (TCCR3B & 0b11111101);		//
	lightOn();							//
}


void activationTimerStop()
{
	TCCR3B = (TCCR3B & 0b11111000);		// Preescaler sættes til 0
	lightOff();
	waitedTime = 0;
}


void activationTimerReset()
{
	waitedTime = 0;						// Timeren resetes
}


void activationClokcReset()
{
	TCNT3 = SEC_TIME;					// Tælleregister sættes til 49911 = 1 sek delay
}


ISR(TIMER3_OVF_vect)					// Interrupt hvert sekund
{
	waitedTime++;						

	if (waitedTime >= PIR_WAIT_TIME)	
	{	
		activationTimerStop();
	}

	activationClokcReset();
}