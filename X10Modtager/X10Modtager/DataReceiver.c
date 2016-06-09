#include "DataReceiver.h"
#include "PirSensor.h"
#include "ActivitySim.h"
#include "Light.h"


void dataReceiverInit()
{
	pirInit();						//
	activitySimInit();				//

	DDRD = (DDRD & 0b11111011);		// S�tter PD2 til indgagn
}


void newMessage()
{
	_delay_us(330);							// Forsinkelse sikre at vi l�ser bite.  330 virker p� fumlebr�t
	
	insertNewBit();							// Inds�t nye bit i bitr�kken

	if (checkForLegitMessage() == 1)		// Check om der er kommet en ny besked
	{
		struct X10Message message = readMessage();		// L�s beskeden
		
		if (message.unit_ == UNIT_ID || message.unit_ == 0)		// Hvis beskeden er til denne enhed eller alle enheder
		{
			interpretMessage(message);		// Forst� besked og udf�r kommandoer
		}
	}
}


void interpretMessage(struct X10Message m)
{
	setLightLevel(m.brightness_);	// S�t den nye lysstyrke

	if (m.mode_ == 0 && pirInterruptCheckRunnig() != 1)			// Hvis PIR respons skal starte, og ikke alderede er aktiv
	{
		activitySimStop();			// Stop Aktivitetssimuleringen
		pirInterruptStart();		// Start PIR-interruptet
	}
	else if (m.mode_ == 1 && activitySimCheckRunning() != 1)	// Hvis Aktivitessimulering skal starte, og ikke aldere er aktiv
	{
		pirInterruptStop();			// Stop PIR-interruptet
		activitySimStart();			// Start Aktivitetssimuleringen
	}
}


void insertNewBit()		// Shifter alle bits i den indl�ste bit �n frem og inds�tter ny bit
{
	char newBit = (PIND & 0b00000100);													// Afl�s databit fra databen.

	firstMessagePart = firstMessagePart << 1;											// Shift r�kke 1, �n til h�jre.
	firstMessagePart = (firstMessagePart | ((secondMessagePart & 0b10000000) >> 7));	// og inds�t bit 7 fra 2. r�kke p� plads 0 i r�kke 1.

	secondMessagePart = secondMessagePart << 1;											// Shift r�kke 2, �n til h�jre
	secondMessagePart = (secondMessagePart | ((thirdMessagePart & 0b10000000) >> 7));	// og inds�t bit 7 fra 3. r�kke p� plads 0 i r�kke 2.

	thirdMessagePart = thirdMessagePart << 1;											// Shift r�kke 3, �n til h�jre
	thirdMessagePart = (thirdMessagePart | ((fourthMessagePart & 0b10000000) >> 7));	// og inds�t bit 7 fra 4. r�kke p� plads 0 i r�kke 3.

	fourthMessagePart = fourthMessagePart << 1;											// Shift r�kke 4, �n til h�jre
	fourthMessagePart = (fourthMessagePart | newBit);									// og inds�t ny bit fra dateben p� plads 2 i r�kke 4.
}


int checkForLegitMessage()
{
	if ((firstMessagePart & 0b11110000) != 0b11100000)	// Chekker for start besked
	{
		return 0;
	}
	
	int i;
	for (i = 0; i <= 1; i++)		// Checker om der er paritet de rigtige steder
	{
		if (getBitValue(firstMessagePart, i) == 0b11111111)
		{
			return 0;
		}
	}
	
	for (i = 0; i <= 3; i++)		// Checker om der er paritet de rigtige steder
	{
		if (getBitValue(secondMessagePart, i) == 0b11111111)
		{
			return 0;
		}
	}

	for (i = 0; i <= 3; i++)		// Checker om der er paritet de rigtige steder
	{
		if (getBitValue(thirdMessagePart, i) == 0b11111111)
		{
			return 0;
		}
	}
	
	for (i = 1; i < 3; i++)			// Checker om der er paritet de rigtige steder
	{
		if (getBitValue(fourthMessagePart, i) == 0b11111111)
		{
			return 0;
		}
	}

	return 1;		// 1 = legit
}


struct X10Message readMessage()	// L�ser X.10 besked
{
	struct X10Message message;

	message.unit_ = getUnitID();
	message.mode_ = getMode();
	message.brightness_ = getBrightness();

	return message;
}


int getUnitID()		// Henter enhedesnummer
{
	char unitID = 0b00000000;
	
	unitID = (unitID | (getBitValue(firstMessagePart, 1) << 4));	// Inds�tter bit fra in-register i unitID
	unitID = (unitID | (getBitValue(firstMessagePart, 0) << 3));	// 
	unitID = (unitID | (getBitValue(secondMessagePart, 3) << 2));	// 
	unitID = (unitID | (getBitValue(secondMessagePart, 2) << 1));	// 
	unitID = (unitID | (getBitValue(secondMessagePart, 1) << 0));	// 

	return unitID;
}


int getMode()		// Henter mode
{
	return getBitValue(secondMessagePart, 0);
}


int getBrightness()		// Henter lysviveau
{
	char brightness = 0b00000000;

	brightness = (brightness | (getBitValue(thirdMessagePart, 3) << 6));	//	Inds�tter bit fra in-registre i brightness
	brightness = (brightness | (getBitValue(thirdMessagePart, 2) << 5));	//	
	brightness = (brightness | (getBitValue(thirdMessagePart, 1) << 4));	//	
	brightness = (brightness | (getBitValue(thirdMessagePart, 0) << 3));	//	
																			// 
	brightness = (brightness | (getBitValue(fourthMessagePart, 3) << 2));	//	
	brightness = (brightness | (getBitValue(fourthMessagePart, 2) << 1));	//	
	brightness = (brightness | (getBitValue(fourthMessagePart, 1) << 0));	//	

	if (brightness > 100)	// Hvis lystyrken er st�re end 100 % s�ttes den til 100.
	{
		brightness = 100;
	}

	return brightness;
}


char getBitValue(char byte, int bitNum)		// Henter bit nr. bitNum ud af X10 Besked.
{
	if (bitNum < 0 && 3 < bitNum)		// Checker f�rst om der bedes om legalt bit.
	{									// Da der i en X.10 bitstreng p� 8 bit kun er 4 reele bit
		return 0b11111111;				// Kan kun 4 (0-3) bit hents.
	}
	
	int bitShift = bitNum * 2;			// 	

	if ((byte & (0b00000011 << bitShift)) == (0b00000001 << bitShift))
	{
		return 0b00000000;				// Det er et '0'.
	}
	else if ((byte & (0b00000011 << bitShift)) == (0b00000010 << bitShift))
	{
		return 0b00000001;				// Det er et '1'.
	}
	else
	{
		return 0b11111111;				// Fejlkode.
	}
}
