/*************************************************************
project: <LcdUI>
author: <Thierry PARIS>
description: <Class for a basic screen>
*************************************************************/

#include "LcdUi.h"
#include "WindowChoice.hpp"

WindowChoice::WindowChoice(byte inFirstLine) : Window(inFirstLine)
{
	this->choiceAddCounter = 0;
	this->choiceValue = 0;
	this->memoChoiceValue = 0;
}

void WindowChoice::AddChoice(byte inStringNumber, byte inInterruptOnEscape)
{
	if (this->choiceAddCounter < WINDOW_MAXCHOICES)
	{
		this->choices[this->choiceAddCounter] = inStringNumber;
		this->escapeWindows[this->choiceAddCounter] = inInterruptOnEscape;
		this->choiceAddCounter++;

		// Set the initial value to the first choice.
		if (this->choiceAddCounter == 1)
			this->choiceValue = inStringNumber;
	}
}

byte WindowChoice::GetChoiceIndex() const
{
	for (byte i = 0; i < this->choiceAddCounter; i++)
		if (choices[i] == this->choiceValue)
			return i;

	return 255;
}

// Get the next choice value from choices, if the current selection is the last one, return to the first...
void WindowChoice::MoveNextChoice()
{
	for (byte i = 0; i < this->choiceAddCounter; i++)
		if (choices[i] == this->choiceValue)
		{
			i++;
			if (i >= this->choiceAddCounter)
				i = 0;
			this->choiceValue = this->choices[i];
			return;
		}

	this->choiceValue = choices[0];
}

// Get the previous choice value from choices, if the current selection is the first one, go to the last...
void WindowChoice::MovePreviousChoice()
{
	for (byte i = 0; i < this->choiceAddCounter; i++)
		if (choices[i] == this->choiceValue)
		{
			i--;
			if (i == 255)
				i = this->choiceAddCounter - 1;
			this->choiceValue = this->choices[i];
			return;
		}

	this->choiceValue = choices[0];
}

void WindowChoice::Event(byte inEventType, LcdUi *inpLcd)
{
	bool showValue = false;
	Screen *pScreen = inpLcd->GetScreen();

	if (this->state == STATE_INITIALIZE)
	{
		this->state = STATE_NONE;
		showValue = true;
	}

	if (this->state == STATE_START)
	{
		pScreen->DisplayHeader(this->GetFirstLine());

		this->state = STATE_INITIALIZE;
	}

	switch (inEventType)
	{
	case EVENT_MORE:
		this->MoveNextChoice();
		showValue = true;
		break;
	case EVENT_LESS:
		this->MovePreviousChoice();
		showValue = true;
		break;
	case EVENT_MOVE:
		break;
	case EVENT_SELECT:
		this->SetState(STATE_CONFIRMED);
		break;
	case EVENT_CANCEL:
		this->SetState(STATE_ABORTED);
		break;
	}

	if (showValue)
	{
		pScreen->DisplayChoice(this->GetChoiceValue());
	}
}