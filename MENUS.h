#ifndef _MENUS_h_
#define _MENUS_h_

#include "avr_ObjLcdLib/LCD.h"
#include "avr_ObjButtonLib/BUTTON.h"
#include "avr_ObjRotaryLib/ROTARYENC.h"

typedef struct {
	char		*text;
	uint8_t	autoUpdateText;
	void		(*autoUpdateHandler) (char *text, int16_t rotation);
	uint16_t	autoUpdateEncAccrl;
	uint8_t	selectable;
	uint8_t	numbering;
	void		(*selectHandler) (void);
} type_MENU_ENTRY;

void MENU_DRAW (type_MENU_ENTRY **ArrayOfEntries, type_LCD *lcd, type_BUTTON *OKButton, type_ROTARYENC *selectEncoder, type_ROTARYENC *editEncoder);
void MENU_LCDINIT (type_LCD *lcd);
void MENU_CREATEHEADER (char *text, char *destination);

#define MENU_CHAR_HEADERSTART	LCD_GC_CHAR4
#define MENU_CHAR_HEADERSTOP	LCD_GC_CHAR5
#define MENU_CHAR_HEADERTOP		LCD_GC_CHAR6
#define MENU_CHAR_HEADERBOTTOM	LCD_GC_CHAR7

#define MENU_END	0
#define MENU_EXIT	0

#define MENU_HEADERWIDTH	16

// in ms:
#define MENU_RERENDER_TIMEOUT 200

// ---
#define None	0


#endif
