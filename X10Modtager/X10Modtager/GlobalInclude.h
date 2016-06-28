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


// Konstant til hvor længe lyset skal være tændt ved PIR-respons.
#define PIR_WAIT_TIME 10	// Tid lyset skal være tændt når PIR sensoren opfanger bevægelse i sekunder. (900 sek = 15 min).
#define PIR_FADE_TIME 5		// Tid lyset skal fade ned til 0 % før lyset slukkes helt.


// Konstanter til Aktivitetssimulering
#define MIN_SIM_TIME 3		// Minimum tid simuleringen skal køre i sekunder.
#define MAX_SIM_TIME 10		// Maximum tid simuleringen kan have tændt / slukket lys.
#define MIN_SIM_LIGHT 25	// Minimum lysstyrke ved aktivitetssmulering.
#define MAX_SIM_LIGHT 100	// Maximum lysstyrke ved aktivitetssimulering.


// 
extern int lightLevel;			// 
extern int lastPirLightLevel;	//

#endif /* GLOBALINCLUDE_H_ */