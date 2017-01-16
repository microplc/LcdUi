/*************************************************************
project: <LcdUi>
author: <Thierry PARIS>
description: <Class for an interruption window>
*************************************************************/

#include "LcdUi.h"
#include "WindowInterrupt.hpp"

WindowInterrupt::WindowInterrupt(byte inFirstLine, byte inSecondLine, byte inEventType, int inTag) : Window(inFirstLine, inTag)
{ 
	this->secondLine = inSecondLine;
	this->eventType = inEventType;
}

void WindowInterrupt::Event(byte inEventType, LcdUi *inpLcd)
{
	if (this->state == STATE_INITIALIZE)
		this->state = STATE_NONE;

	if (this->state == STATE_START)
	{
		inpLcd->GetScreen()->DisplayHeader(this->firstLine);
		inpLcd->GetScreen()->DisplayText(this->secondLine, 0, 1);

		this->state = STATE_INITIALIZE;
	}
}

#ifdef LCDUI_PRINT_WINDOWS
void WindowInterrupt::printWindow()
{
	printWindowHeader(F("Window Interrupt"));
	Serial.print(F(" / SecondLine: "));
	Serial.print(this->secondLine);
	Serial.print(F(" / EventType: "));
	Serial.println(this->eventType);
}
#endif