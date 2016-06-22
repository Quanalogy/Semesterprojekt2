#include "Light.h"

void lightInit()
{
	DDRB = (DDRB | 0b10000000);				// Sætter PB til udgang
	PORTB = (PORTB & 0b01111111);			//

	TCCR1A = (TCCR1A | 0b00000010);			// Timer-mode sættes til mode 2 (9 bit fasekorrekt)
	TCCR1B = (TCCR1B | 0b00000000);			//
		
	setLightLevel(70);						// Standart værdi angives

	lightOff();
}


void setLightLevel(int duty)
{
	if (duty > 100)
		duty = 100;

	lightLevel = duty;
}


void setLastPirLightLevel(int duty)
{
	if (duty > 100)
		duty = 100;

	lastPirLightLevel = duty;
}


void setPwmTimer(int duty)
{
	OCR1C = (-((duty * 0.01) - 1) * 512);	// C-systemet bruges.
}


void lightOn()
{
	TCCR1B = (TCCR1B | 0b00000100);			// Prescaler sættes til 256 for at tænde.
	TCCR1A = (TCCR1A | 0b00001100);			// C-systemes udgangs operationer vælges.

	if (lightLevel == 0)
	{
		setPwmTimer(0);
	}
	else
	{
		setPwmTimer(lightLevel);
	}
}


void lightOff()
{
	TCCR1B = (TCCR1B & 0b11111000);		// Preescaler sættes til 0 for at slukke.
	TCCR1A = (TCCR1A & 0b11110011);		// Normal Port operation vælges.
	
	setPwmTimer(0);
}


void lightInvert()
{
	if ((TCCR1B & 0b00000111) == 0b00000100 && (TCCR1A & 0b00001100) == 0b00001100)	// Checker om lyset er tændt.
	{
		lightOff();
	}
	else if ((TCCR1B & 0b00000111) == 0b00000000 && (TCCR1A & 0b00001100) == 0b00000000)	// Checker om lyset er slukket.
	{
		lightOn();
	}
	else
	{
		lightOn();
	}
}