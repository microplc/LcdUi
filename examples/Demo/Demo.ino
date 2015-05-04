/*************************************************************
project: <LCD User Interface>
author: <Thierry PARIS>
description: <LCD UI demo>
*************************************************************/

#include "LcdUi.h"

const char  str_dc[] PROGMEM = "Dc";
const char  str_dcc[] PROGMEM = "Dcc";
const char  str_cv[] PROGMEM = "Cv";
const char  str_stop[] PROGMEM = "Arret Alim";
const char  str_stop2[] PROGMEM = "Appuyer Rouge";
const char  str_dcdcc[] PROGMEM = "Change DC/DCC";
const char  str_dcdcc2[] PROGMEM = "Redémarrer/annul";
const char  str_modemodechoice[] PROGMEM = "Choix du mode :";
const char  str_modelococtrl[] PROGMEM = "Controle loco";
const char  str_modelocoedit[] PROGMEM = "Edition loco";
const char  str_modelocoprogram[] PROGMEM = "Program loco";
const char  str_modeacccontrol[] PROGMEM = "Controle acces";
const char  str_modeaccedit[] PROGMEM = "Edition access";
const char  str_modeconfig[] PROGMEM = "Config DDC";
const char  str_locoselect[] PROGMEM = "Choix de loco";
const char  str_resetconfig[] PROGMEM = "Reset Config";
const char  str_yes[] PROGMEM = "oui";
const char  str_no[] PROGMEM = "non";
const char  str_confirm[] PROGMEM = "Sur ?";
const char  str_bkltconfig[] PROGMEM = "Rétro éclairage";
const char  str_incconfig[] PROGMEM = "Vit Incrément";
const char  str_nameconfig[] PROGMEM = "Nom";
const char  str_loconew[] PROGMEM = "Nouvelle Loco";
const char  str_locodel[] PROGMEM = "Supprimer loco";
const char  str_locoedit[] PROGMEM = "Editer loco";
const char  str_splash1[] PROGMEM = "LcdUI Demo 0.1";
const char  str_splash2[] PROGMEM = "By ... you !";

const char * const string_table[] PROGMEM =
{
	str_dc,
	str_dcc,
	str_cv,
	str_stop,
	str_stop2,
	str_dcdcc,
	str_dcdcc2,
	str_modemodechoice,
	str_modelococtrl,
	str_modelocoedit,
	str_modelocoprogram,
	str_modeacccontrol,
	str_modeaccedit,
	str_modeconfig,
	str_locoselect,
	str_resetconfig,
	str_yes,
	str_no,
	str_confirm,
	str_bkltconfig,
	str_incconfig,
	str_nameconfig,
	str_loconew,
	str_locodel,
	str_locoedit,
	str_splash1,
	str_splash2
};

#define STR_DC		0
#define STR_DCC		1
#define STR_CV		2
#define STR_STOP	3
#define STR_STOP2	4
#define STR_DCDCC	5
#define STR_DCDCC2	6
#define STR_MODEMODECHOICE	7
#define STR_MODELOCOCTRL	8
#define STR_MODELOCOEDIT	9
#define STR_MODELOCOPROGRAM	10
#define STR_MODEACCCONTROL	11
#define STR_MODEACCEDIT		12
#define STR_MODECONFIG		13
#define STR_LOCOSELECT		14
#define STR_RESETCONFIG		15
#define STR_YES			16
#define STR_NO			17
#define STR_CONFIRM		18
#define STR_BACKLIGHTCFG	19
#define STR_INCCFG		20
#define STR_NAMECFG		21
#define STR_LOCONEW		22
#define STR_LOCOREMOVE		23
#define STR_LOCOEDIT		24
#define STR_SPLASH1		25
#define STR_SPLASH2		26

LcdUi lcd;
ScreenTwoLines screen;

int incValue;
bool backlight;
char name[80];

void setup()
{
	LcdUi::StartSetup();

	screen.Setup(16, 2, string_table, 0, 1, 2, 3, 4, 5, 6);
	Screen::YesMsg = 16;
	Screen::NoMsg = 17;
	lcd.Setup(&screen, 10);

	WindowSplash *pSplash = (WindowSplash *)lcd.AddWindow(new WindowSplash(STR_SPLASH1, STR_SPLASH2, 500));	// Splash screen
	WindowChoice *pChoiceMain = (WindowChoice *)lcd.AddWindow(new WindowChoice(STR_MODEMODECHOICE));	// menu
	pChoiceMain->AddChoice(STR_MODECONFIG);
		WindowChoice *pChoiceConfig = (WindowChoice *)lcd.AddWindow(new WindowChoice(STR_MODECONFIG), pChoiceMain, 0);	// config
		pChoiceConfig->AddChoice(STR_INCCFG);
			lcd.AddWindow(new WindowInt(STR_INCCFG), pChoiceConfig, 0);	// config incValue
		pChoiceConfig->AddChoice(STR_NAMECFG);
			lcd.AddWindow(new WindowText(STR_NAMECFG, 10), pChoiceConfig, 1);	// config name
		pChoiceConfig->AddChoice(STR_BACKLIGHTCFG);
			lcd.AddWindow(new WindowYesNo(STR_BACKLIGHTCFG), pChoiceConfig, 2);	// config backlight
		pChoiceConfig->AddChoice(STR_RESETCONFIG);
			lcd.AddWindow(new WindowConfirm(STR_RESETCONFIG, STR_CONFIRM), pChoiceConfig, 3);	// reset config 
	pChoiceMain->AddChoice(STR_MODELOCOCTRL);
		lcd.AddWindow(new Window(STR_MODELOCOCTRL), pChoiceMain, 1); // run

	lcd.AddWindow(new WindowInterrupt(STR_STOP, STR_STOP2)); // Emergency stop
	lcd.AddWindow(new WindowInterrupt(STR_DCDCC, STR_DCDCC2)); // Mode Dc/DCC change

	incValue = 10;
	backlight = false;
	strcpy(name, "Test");

	LcdUi::EndSetup();
}

void loop()
{
	int event = EVENT_NONE;

#if VISUALSTUDIO
	if (theApp.lastKeyPressed != 0)
	{
		switch (theApp.lastKeyPressed)
		{
		case '+':	event = EVENT_MORE; break;
		case '-':	event = EVENT_LESS; break;
		case '*':	event = EVENT_SELECT; break;
		case '/':	event = EVENT_CANCEL; break;
		}

		Serial.print(F("Keyboard "));
		char str[3];
		str[0] = theApp.lastKeyPressed;
		str[1] = 0;
		Serial.print(str);
		Serial.println(F(" pressed "));

		theApp.lastKeyPressed = 0;
	}
#endif

	if (event != EVENT_NONE || lcd.GetState() != STATE_NONE || lcd.GetCurrentWindow()->GetType() == WINDOWTYPE_SPLASH)
	{
		lcd.Loop(event);

		switch (lcd.GetState())
		{
		case STATE_INITIALIZE:
			switch (lcd.GetWindowId())
			{
			case STR_INCCFG:
				lcd.GetCurrentWindow()->SetValue(incValue);
				break;
			case STR_NAMECFG:
				lcd.GetCurrentWindow()->SetValue(name);
				break;
			case STR_BACKLIGHTCFG:
				lcd.GetCurrentWindow()->SetChoiceValue(backlight ? Screen::YesMsg : Screen::NoMsg);
				break;
			}
			break;

		case STATE_CONFIRMED:
			switch (lcd.GetWindowId())
			{
			case STR_INCCFG:
				incValue = lcd.GetCurrentWindow()->GetIntValue();
				break;
			case STR_NAMECFG:
				strcpy(name, lcd.GetCurrentWindow()->GetTextValue());
				break;
			case STR_BACKLIGHTCFG:
				backlight = lcd.GetCurrentWindow()->GetChoiceValue() == Screen::YesMsg;
				break;
			}
			lcd.SetState(STATE_POSTCONFIRMED);
			break;

		}
	}
}