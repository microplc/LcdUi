/*************************************************************
project: <LcdUI>
author: <Thierry PARIS>
description: <Class for a basic screen>
*************************************************************/

#include "LcdUi.h"
#include "Screen.hpp"

char Screen::buffer[80];
int Screen::YesMsg;
int Screen::NoMsg;

void Screen::Setup(byte inSizeX, byte inSizeY, const char * const *inpStringTable)
{
	this->sizex = inSizeX;
	this->sizey = inSizeY;
	this->pStringTable = inpStringTable;

#ifdef VISUALSTUDIO
	pScreenVS->Setup(sizex, sizey);
#endif
}

void Screen::clearLine(int posy)
{
	memset(Screen::buffer, 32, this->sizex);
	Screen::buffer[this->sizex] = 0;

	this->setCursor(0, posy);
	this->print(Screen::buffer);
}

void Screen::BuildString(int inValue, char *outString, int digits)
{
	int pows_of_ten[6] = { 1, 10, 100, 1000, 10000 };
	int nb = digits;
	if (digits > 0 && digits < 6)
	{
		inValue = inValue%pows_of_ten[digits];
		for (; nb > 0; nb--)
		{
			if (inValue < pows_of_ten[nb - 1])
			{
				outString[digits - nb] = '0';
				continue;
			}
			outString[digits - nb] = (char)(48 + inValue / pows_of_ten[nb - 1]);
			inValue = inValue % pows_of_ten[nb - 1];
		}
		outString[digits] = 0;
	}
	else
	{
		if (inValue == 0)
		{
			outString[0] = '0';
			outString[1] = 0;
			return;
		}

		signed int started = -1;
		for (nb = 5; nb > 0; nb--)
		{
			if (started < 0 && inValue >= pows_of_ten[nb - 1])
				started = nb;
			if (started >= 0)
			{
				outString[started - nb] = (char)(48 + (inValue / pows_of_ten[nb - 1]));
				inValue = inValue % pows_of_ten[nb - 1];
			}
		}
		outString[started] = 0;
	}
}

void Screen::BuildProgress(byte inValue, byte inMax, bool inFromLeftDir, byte inLengthString, char *outString)
{
	byte localValue = (byte) ((int)(inLengthString-2) * (((double)inValue) / inMax));
	if (localValue == 0 && inValue > 0)
		localValue = 1;

	if (localValue == inLengthString - 2 && inValue < inMax)
		localValue--;

	memset(outString, 32, inLengthString - 1);
	outString[inLengthString] = 0;

	if (inFromLeftDir)
	{
		outString[0] = '-';
		outString[inLengthString - 1] = '+';
		memset(outString+1, '>', localValue);
	}
	else
	{
		outString[0] = '+';
		outString[inLengthString - 1] = '-';
		memset(outString + inLengthString - 1 - localValue, '<', localValue);
	}
}

byte Screen::BuildStringLeft(const char *inString, byte inSizeMax, char *outString)
{
	memcpy(outString, inString, inSizeMax);
	outString[inSizeMax] = 0;

	int len = strlen(outString);
	if (len > inSizeMax)
		len = inSizeMax;

	return len;
}

char *Screen::GetString(int inString)
{
#ifdef VISUALSTUDIO
	strcpy_s(buffer, 80, this->pStringTable[inString]);
#else
	strcpy_P(buffer, (char*)pgm_read_word(&this->pStringTable[inString]));
#endif

	return buffer;
}

byte Screen::GetChar(int inPos)
{
	if (inPos < 0 || inPos > 127)
		return ' ';

	if (inPos == 0)
		return 4;	// validated !

	if (inPos == 1)
		return 5;	// backspace

	return 32 + (inPos - 2);
}
