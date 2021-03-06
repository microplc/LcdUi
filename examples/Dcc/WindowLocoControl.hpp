//-------------------------------------------------------------------
#ifndef __windowLocoControl_H__
#define __windowLocoControl_H__
//-------------------------------------------------------------------
#include "LcdUi.h"
//-------------------------------------------------------------------

#define WINDOWTYPE_LOCOCONTROL	100

class WindowLocoControl : public Window
{
public:
	int Address;
	byte AddressSize;
	byte Speed;
	byte SpeedMax;
	int Speed128Inc;	// int only because of the editing window which accepts only ints...
	bool Direction;
	char Name[20];

public:
	WindowLocoControl();

	inline byte GetType() const { return WINDOWTYPE_LOCOCONTROL; }
	void Event(byte inEventType, LcdUi *inpLcd);

	void printWindow() { Serial.println("WindowLocoControl"); }
};

#endif
//-------------------------------------------------------------------
