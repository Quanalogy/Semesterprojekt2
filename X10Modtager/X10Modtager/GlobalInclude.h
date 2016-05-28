#ifndef GLOBALINCLUDE_H_
#define GLOBALINCLUDE_H_

#define F_CPU 16000000
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "uart.h"		//Debug

// Enhedes ID nr.
#define UNIT_ID 20


// Konstant til 1-sekunds timere
#define SEC_TIME 49911		// 1 sek


// Konstant til hvor l�nge lyset skal v�re t�ndt ved PIR-respons
#define PIR_WAIT_TIME 900	// Tid lyset skal v�re t�ndt n�r PIR sensoren opfanger bev�gelse i sekunder. (900 sek = 15 min)


// Konstanter til Aktivitetssimulering
#define MAX_SIM_TIME 90		// Maximum tid simuleringen kan have t�ndt / slukket lys
#define MIN_SIM_TIME 15		// Minimum tid simuleringen skal k�re i sekunder


#endif /* GLOBALINCLUDE_H_ */