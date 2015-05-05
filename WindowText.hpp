//-------------------------------------------------------------------
#ifndef __windowText_H__
#define __windowText_H__
//-------------------------------------------------------------------

//-------------------------------------------------------------------

#include "Window.hpp"
#include "string.h"

//-------------------------------------------------------------------

#define WINDOW_MAXTEXTVALUESIZE	20

#define STATE_SELECTCHAR	100
#define STATE_SELECTBACK	101

class WindowText : public Window
{
private:
	byte maxTextValueLength;
	byte currentCharPos;
	byte currentCharEdited;
	char textValue[WINDOW_MAXTEXTVALUESIZE + 1], memoTextValue[WINDOW_MAXTEXTVALUESIZE + 1];

public:
	WindowText(byte inFirstLine, byte inMaxLengthValue = WINDOW_MAXTEXTVALUESIZE);

	inline byte GetType() const { return WINDOWTYPE_TEXT; }
	inline byte GetMaxTextValueLength() const { return this->maxTextValueLength; }
	inline void SetMaxTextValueLength(byte inLength) { this->maxTextValueLength = inLength; }

	inline const char *GetTextValue() const { return this->textValue; }
	inline void SetValue(const char *inValue) { STRCPY(this->textValue, inValue); }

	void Event(byte inEventType, LcdUi *inpLcd);
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