#include "ZeroCrossing.h"
#include "DataReceiver.h"


void zeroCrossInit()
{
	dataReceiverInit();				// 

	DDRE = (DDRE & 0b11101111);		// PE4 sættes til indgang.
	PORTE = (PORTE & 0b11101111);	// Udgangssignalet på PE4 sættes lav, bare for at være sikker.
	EICRB = (EICRB | 0b00000001);	// Interrupt på både risng og falling edge
	
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