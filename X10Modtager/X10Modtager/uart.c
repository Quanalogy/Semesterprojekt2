#include <avr/io.h>
#include <stdlib.h>
#include "uart.h"

void InitUART(unsigned long BaudRate, unsigned char DataBit, char Parity)
{
	if(BaudRate >= 110 && BaudRate <= 115200 && DataBit >= 5 && DataBit <= 8)
	{
		// RX & TX
		UCSR0B = (UCSR0B | 0b00011000);
		
		// Parity
		if (Parity == 'E')
		{
			UCSR0C = (UCSR0C | 0b00100000);
		}
		else if (Parity == 'O')
		{
			UCSR0C = (UCSR0C | 0b00110000);
		}
		else if (Parity == 'N')
		{
			
		}
		
		// Databit
		switch (DataBit)
		{
			case 5:
			UCSR0C = (UCSR0C | 0b00000000);
			break;
			
			case 6:
			UCSR0C = (UCSR0C | 0b00000010);
			break;
			
			case 7:
			UCSR0C = (UCSR0C | 0b00000100);
			break;
			
			case 8:
			UCSR0C = (UCSR0C | 0b00000110);
			break;
		}
		
		//BaudRate
		UBRR0 = ((16000000 / (16 * BaudRate)) - 1);
	}
}

unsigned char CharReady()
{
	return UCSR0A & (1<<7);
}

char ReadChar()
{
	while((UCSR0A & 0b10000000) == 0)
	{
		
	}
	return UDR0;
}

void SendChar(char Tegn)
{
	while((UCSR0A & 0b00100000) == 0)
	{
			
	}
	UDR0 = Tegn;
}

void SendString(char* Streng)
{
	int i = 0;
	
	while(Streng[i] != 0)
	{
		SendChar(Streng[i]);
		i++;
	}
}

void SendInteger(int Tal)
{
	char outputStr[7];
	
	itoa(Tal, outputStr, 10);
	
	SendString(outputStr);
}