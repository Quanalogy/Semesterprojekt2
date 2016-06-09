#ifndef DATARECEIVER_H_
#define DATARECEIVER_H_

#include "GlobalInclude.h"
#include "X10Message.h"

// Variabler				// En fuld X.10 besked er 30 bit lang og kan
char firstMessagePart;		// derfor ikke være i et register.
char secondMessagePart;		// Bitsne bliver derfor sat ind i "fourthMessagePart"
char thirdMessagePart;		// og bliver derefter shiftet op igennem disse registre
char fourthMessagePart;		// og bliver derefter læst og afkodet herfra.

// Funktioner
void dataReceiverInit();

void newMessage();
void interpretMessage(struct X10Message);

void insertNewBit();
int checkForLegitMessage();

struct X10Message readMessage();

int getUnitID();
int getMode();
int getBrightness();

char getBitValue(char, int);// Henter paritiseret bitværdi ved bit nr. 3-0 i char. 
							// Returnere -1 ved fejl.

#endif /* DATARECEIVER_H_ */