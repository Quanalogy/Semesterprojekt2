#include "Light.h"
#include "uart.h"

void lightInit()				// Testet - Virker
{
	DDRB = (DDRB | 0b10000000);			// S�tter PB til udgang
	PORTB = (PORTB & 0b01111111);		//

	TCCR1A = (TCCR1A | 0b00000010);		// Timer-mode s�ttes til mode 2 (9 bit fasekorrekt)
	TCCR1B = (TCCR1B | 0b00000000);		//

	lightOff();
}


void setLightLevel(int duty)	// Testet - Virker
{
	if (duty == 0)
		lightOff();
	else
		lightOn();

	OCR1C = (-((duty * 0.01) - 1) * 512);	// C-systemet bruges	
}


void lightOn()					// Testet - Virker
{
	TCCR1B = (TCCR1B | 0b00000100);		// Prescaler s�ttes til 256 for at t�nde
	TCCR1A = (TCCR1A | 0b00001100);		// C-systemes udgangs operationer v�lges.
}


void lightOff()					// Testet - Virker
{
	TCCR1B = (TCCR1B & 0b11111000);		// Prescaler s�ttes til 0 for at slukke
	TCCR1A = (TCCR1A & 0b11110011);		// Normal Port operation v�lges
}


void lightInvert()				// Testet - Virker
{
	if ((TCCR1B & 0b00000111) == 0b00000100 && (TCCR1A & 0b00001100) == 0b00001100)
	{
		lightOff();
	}
	else if ((TCCR1B & 0b00000111) == 0b00000000 && (TCCR1A & 0b00001100) == 0b00000000)
	{
		lightOn();
	}
	else
	{
		lightOn();
	}
}