#include "ActivationTimer.h"
#include "uart.h"

int waitedTime = 0;

void activationTimerInit()
{
	TCCR3A = (TCCR3A & 0b11111100);		// Normal mode v�lges
	TCCR3B = (TCCR3B & 0b11100111);		//

	TCCR3B = (TCCR3B | 0b00000101);		// Preescaler s�ttes til 1024
	TCCR3B = (TCCR3B & 0b11111101);		// 

	TCNT3  = sec_time;					// T�lleregister s�ttes til 49911

	TIMSK3 = (TIMSK3 | 0b00000001);		// Interrupt enable

	sei();
}


void activationTimerStart()
{
	TCCR3B = (TCCR3B | 0b00000101);		// Preescaler s�ttes til 1024
	TCCR3B = (TCCR3B & 0b11111101);		//
	activationTimerReset();
}


void activationTimerStop()
{
	TCCR3B = (TCCR3B & 0b11111000);		// Preescaler s�ttes til 0
}


void activationTimerReset()
{
	TCNT3 = sec_time;
}


ISR(TIMER3_OVF_vect)
{
	if (waitedTime >= wait_time)
	{
		

		waitedTime = 0;
	}
	else
	{
		waitedTime++;
	}
	
	SendInteger(waitedTime);
	SendChar('\n');

	activationTimerReset();
	sei();
}