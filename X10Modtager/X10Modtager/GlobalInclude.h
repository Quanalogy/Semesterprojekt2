#ifndef GLOBALINCLUDE_H_
#define GLOBALINCLUDE_H_

#define F_CPU 16000000
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "uart.h"		//Debug

// Enhedes ID nr.
#define UNIT_ID 3


// Konstant til 1-sekunds timere
#define SEC_TIME 49911		// 1 sek


// Konstant til hvor længe lyset skal være tændt ved PIR-respons
#define PIR_WAIT_TIME 3		// Tid lyset skal være tændt når PIR sensoren opfanger bevægelse i sekunder. (900 sek = 15 min)


// Konstanter til Aktivitetssimulering
#define MIN_SIM_TIME 2		// Minimum tid simuleringen skal køre i sekunder
#define MAX_SIM_TIME 5		// Maximum tid simuleringen kan have tændt / slukket lys


#endif /* GLOBALINCLUDE_H_ */