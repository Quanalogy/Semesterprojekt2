#include "ZeroCrossing.h"
#include "DataReceiver.h"


void zeroCrossInit()
{
	dataReceiverInit();				// 

	DDRE = (DDRE & 0b11101111);		// PE4 s�ttes til indgang.
	PORTE = (PORTE & 0b11101111);	// Udgangssignalet p� PE4 s�ttes lav, bare for at v�re sikker.
	EICRB = (EICRB | 0b00000001);	// Interrupt p� b�de risng og falling edge
	
	sei();							// Global interrupt tilladt
}


void activateZeroCrossInterrupt()
{
	EIMSK = (EIMSK | 0b00010000);	// Interrupt fra INT4 tilladt
}


void deactivateZeroCrossInterrupt()
{
	EIMSK = (EIMSK & 0b11101111);	// Interrupt fra INT4 ikke tilladt
}


ISR(INT4_vect)
{
	newMessage();					// Nyt zero cross

	EIFR = (EIFR | 0b00010000);		// Reset interrupt flag
}