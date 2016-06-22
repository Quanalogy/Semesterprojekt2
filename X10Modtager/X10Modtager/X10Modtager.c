// Koder til styring af X.10 Modtager til Semester Projekt 2.
// Ver. 1.1
// 22/6 - 2016
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

int main(void)
{
	zeroCrossInit();				// Initere zero Crossing og alle underliggende systemer.
	pirInterruptStart();			// Starter i PIR respons stadige.
	activateZeroCrossInterrupt();	// Aktivere interuptet fra zero cross detector, kan nu modtage data med X10.

	while(1)
	{
		
	}
}
