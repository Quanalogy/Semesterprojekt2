#include "GlobalInclude.h"
#include "PirSensor.h"
#include "ZeroCrossing.h"
#include "X10Message.h"
#include "DataReceiver.h"
#include "uart.h"
#include "ActivationTimer.h"
#include "Light.h"

const int unitID = 1;

int inactivityBrightness = 0;
int activityBrightness = 100;

int main(void)
{
	//InitUART(9600, 8, 'N');
	//activationTimerInit();
	//lightInit();
	//pirInit();
	//activatePirInterrupt();

	//SendChar('\n');			// Debug
	//SendChar('S');			//
	
	//lightOn();
	//_delay_ms(200);
	//lightOff();
	//_delay_ms(200);


	DDRB = (DDRB | 0b10000000);		// S�tter PB til udgang
	PORTB = (PORTB & 0b01111111);

	TCCR1A = (TCCR1A | 0b00000010);	//
	TCCR1B = (TCCR1B | 0b00000000);	// Timer-mode s�ttes til mode 2 (9 bit fasekorrekt)

	TCCR1B = (TCCR1B | 0b00000100);	// Preescaler s�ttes til 256
	
	TCCR1A = (TCCR1A | 0b00001100);	// S�tter C-system on compare, when up-counting

	while(1)
	{
		
	}
}