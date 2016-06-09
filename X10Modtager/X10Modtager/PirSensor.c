#include "PirSensor.h"
#include "ActivationTimer.h"

void pirInit()
{
	activationTimerInit();
	
	PORTE = (PORTE | 0b00000000);	// PE5 initieres til en indgang
	PINE = (PINE | 0b00000000);		// og udgangs værdi sættes til '0'.
	DDRE = (DDRE & 0b11011111);		//

	EICRB = (EICRB | 0b00001100);	// Interrupt on rising edge.

	pirInterruptStop();				// Slukker for PIR-interruptet, tændes senere.
	sei();							// Global interrupt enable.
}


int pirScan()
{
	if ( ( PINE & 0b00100000 ) == 0b00000000 )	// Checker om PIR-sensor opfanger bevægelse. (Ikke et interrupt)
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
	EIMSK = (EIMSK | 0b00100000);	// Lokal interrupt enable for INT5.
}


void pirInterruptStop()
{
	EIMSK = (EIMSK & 0b11011111);	// Lokal interrupt disable for INT5.
}


int pirInterruptCheckRunnig()		// Checker om PIR-interruptet er aktivt ved at kigge på lokal interrupt enablebit.
{
	if ((EIMSK & 0b00100000) == 0b00100000)
		return 1;
	else
		return 0;
}


ISR(INT5_vect)						// Interrupt funktion.
{
	activationTimerStart();
}