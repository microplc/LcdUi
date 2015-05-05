//-------------------------------------------------------------------
#ifndef __screenTwoLines_H__
#define __screenTwoLines_H__
//-------------------------------------------------------------------

//-------------------------------------------------------------------

#include "Screen.hpp"
#ifdef VISUALSTUDIO
#include "LiquidCrystalFast.h"
#include "ScreenVS.hpp"
#else
#include "LiquidCrystalFast.hpp"
#endif

#define NBLINES		4
#define NBCHARS		41
#define LENLINE		(NBCHARS-1)

//-------------------------------------------------------------------

class ScreenTwoLines: public Screen
{
private:
	LiquidCrystalFast *pLcd;

public:
	ScreenTwoLines() : Screen() 
	{ 
		this->pLcd = 0; 
#ifdef VISUALSTUDIO
		this->pScreenVS = new ScreenVS();
#endif
	}

	void Setup(byte inSizeX, byte inSizeY, PGM_P const *inpStringTable, 
		uint8_t rs, uint8_t rw, uint8_t enable, uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3);

	// LCD API
	//LibraryName
#ifndef VISUALSTUDIO
	void print(const __FlashStringHelper *inString);
#endif
	void print(const char *inString);
	void print(int inValue, char inType);
	void write(char inValue);
	void clear();
	void home();
	void setCursor(byte Col, byte Row);
	void cursor_on();
	void cursor_off();
	void blink_on();
	void blink_off();
	/////////////

	void DisplayHeader(int inHeader);
	void DisplayChoice(int inCurrentChoice);
	void DisplayChoice(const char *inChoice);
	void DisplayInt(int inValue);
	void DisplayTextResult(const char *inTextValue, byte inLength, byte inEditedChar);
	void DisplayTextChoice(byte inPos, byte inEditedChar);
	void DisplayYesNo(byte inChoiceValue, int prefixString = 0);
};

//-------------------------------------------------------------------

//===================================================================
// -> DO NOT WRITE ANYTHING BETWEEN HERE...
// 		This section is reserved for automated code generation
// 		This process tries to detect all user-created
// 		functions in main_sketch.cpp, and inject their  
// 		declarations into this file.
// 		If you do not want to use this automated process,  
//		simply delete the lines below, with "&MM_DECLA" text 
//===================================================================
//---- DO NOT DELETE THIS LINE -- @MM_DECLA_BEG@---------------------
//---- DO NOT DELETE THIS LINE -- @MM_DECLA_END@---------------------
// -> ...AND HERE. This space is reserved for automated code generation!
//===================================================================


//-------------------------------------------------------------------
#endif
//-------------------------------------------------------------------