#include "PirSensor.h"
#include "ActivationTimer.h"

void pirInit()
{
	activationTimerInit();
	
	PORTE = (PORTE | 0b00000000);	// PE5 initieres til en indgang.
	PINE = (PINE | 0b00000000);		//
	DDRE = (DDRE & 0b11011111);		//

	EICRB = (EICRB | 0b00001100);	// Interrupt on rising edge.

	pirInterruptStop();
	sei();	
}


int pirScan()
{
	if ( ( PINE & 0b00100000 ) == 0b00000000 )
	{
		return 1;
	}
	else
	{
		return 0;
	}
}


void pirInterruptStart()
{
	EIMSK = (EIMSK | 0b00100000);	// Lokal interrupt enable for INT5
}


void pirInterruptStop()
{
	EIMSK = (EIMSK & 0b11011111);
}


int pirInterruptCheckRunnig()		// Testet - Virker
{
	if ((EIMSK & 0b00100000) == 0b00100000)
		return 1;
	else
		return 0;
}


ISR(INT5_vect)
{
	activationTimerStart();
}