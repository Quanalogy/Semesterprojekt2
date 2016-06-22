#ifndef GLOBALINCLUDE_H_
#define GLOBALINCLUDE_H_

#define F_CPU 16000000
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>


// Enhedes ID nr.
#define UNIT_ID 1


// Konstant til 1-sekunds timere
#define SEC_TIME 49911		// 1 sek.


// Konstant til hvor l�nge lyset skal v�re t�ndt ved PIR-respons.
#define PIR_WAIT_TIME 10	// Tid lyset skal v�re t�ndt n�r PIR sensoren opfanger bev�gelse i sekunder. (900 sek = 15 min).
#define PIR_FADE_TIME 5		// Tid lyset skal fade ned til 0 % f�r lyset slukkes helt.


// Konstanter til Aktivitetssimulering
#define MIN_SIM_TIME 3		// Minimum tid simuleringen skal k�re i sekunder.
#define MAX_SIM_TIME 10		// Maximum tid simuleringen kan have t�ndt / slukket lys.
#define MIN_SIM_LIGHT 25	// Minimum lysstyrke ved aktivitetssmulering.
#define MAX_SIM_LIGHT 100	// Maximum lysstyrke ved aktivitetssimulering.


// 
extern int lightLevel;			// 
extern int lastPirLightLevel;	//

#endif /* GLOBALINCLUDE_H_ */