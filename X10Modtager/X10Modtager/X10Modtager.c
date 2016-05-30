// Koder til styring af X.10 Modtager til Semester Projekt 2.
// Ver. 0.9 - Klar til test
// xx/xx - 2016
//
// Zero Cross Detector	PE4	Arduino ben 2	Ext Int 4
// Data					PD2	Arduino ben 19	
// PIR-sensor			PE5	Arduino ben 3	Ext Int 5
// Lys					PB7	Arduino ben 13	Timer 1	C-System	Mode 2 (9-bit fasekorrekt PWM)	Prescaler: 256
// ActivationTimer (1s)	--	--				Timer 3				Mode 0 (Normal 16-bit)			Prescaler: 1024
// Aktiviters Simulering--	--				Timer 4				Mode 0 (Normal 16-bit)			Prescaler: 1024		


#include "GlobalInclude.h"
#include "ZeroCrossing.h"
#include "PirSensor.h"

#include "DataReceiver.h"
#include "X10Message.h"

int main(void)
{
	DDRA = 0b00000001;
	InitUART(9600, 8, 'N');			// Debug

	zeroCrossInit();				// Initere zero Crossing og alle underliggende systemer.
	pirInterruptStart();			// Starter i PIR respons stadige
	activateZeroCrossInterrupt();	// 

	//struct X10Message m;
	//m.unit_ = 1;
	//m.mode_ = 1;
	//m.brightness_ = 80;

	//interpretMessage(m);

	while(1)
	{
		
	}
}
