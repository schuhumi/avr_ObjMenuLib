#include <avr/io.h>
#include <util/delay.h>
#include "MENUS.h"
#include "avr_ObjLcdLib/LCD.h"
#include "avr_ObjButtonLib/BUTTON.h"
#include "avr_ObjRotaryLib/ROTARYENC.h"

void MENU_LCDINIT (type_LCD *lcd)
{
	uint8_t chrdata_arrowDown[8] = {
		0b00001010,
		0b00001010,
		0b00001010,
		0b00001010,
		0b00001010,
		0b00011111,
		0b00001110,
		0b00000100
	};
	
	uint8_t chrdata_arrowUp[8] = {
		0b00000100,
		0b00001110,
		0b00011111,
		0b00001010,
		0b00001010,
		0b00001010,
		0b00001010,
		0b00001010
	};
	
	uint8_t chrdata_stopUp[8] = {
		0b00011100,
		0b00000010,
		0b00011010,
		0b00001010,
		0b00001010,
		0b00001010,
		0b00001010,
		0b00001010
	};
	
	uint8_t chrdata_stopDown[8] = {
		0b00001010,
		0b00001010,
		0b00001010,
		0b00001010,
		0b00001010,
		0b00011010,
		0b00000010,
		0b00011100
	};
	
	uint8_t chrdata_headerStart[8] = {
		0b00011100,
		0b00000010,
		0b00011010,
		0b00001010,
		0b00001010,
		0b00001010,
		0b00000111,
		0b00000000
	};
	
	uint8_t chrdata_headerStop[8] = {
		0b00000111,
		0b00001000,
		0b00001011,
		0b00001010,
		0b00001010,
		0b00001010,
		0b00011100,
		0b00000000
	};
	
	uint8_t chrdata_headerTop[8] = {
		0b00011111,
		0b00000000,
		0b00011111,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000
	};
	
	uint8_t chrdata_headerBottom[8] = {
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00011111,
		0b00000000,
		0b00011111
	};
	
	LCD_GENERATECHAR(lcd, LCD_GC_CHAR0, chrdata_arrowDown);
	LCD_GENERATECHAR(lcd, LCD_GC_CHAR1, chrdata_arrowUp);
	LCD_GENERATECHAR(lcd, LCD_GC_CHAR2, chrdata_stopDown);
	LCD_GENERATECHAR(lcd, LCD_GC_CHAR3, chrdata_stopUp);
	LCD_GENERATECHAR(lcd, MENU_CHAR_HEADERSTART, chrdata_headerStart);
	LCD_GENERATECHAR(lcd, MENU_CHAR_HEADERSTOP, chrdata_headerStop);
	LCD_GENERATECHAR(lcd, MENU_CHAR_HEADERTOP, chrdata_headerTop);
	LCD_GENERATECHAR(lcd, MENU_CHAR_HEADERBOTTOM, chrdata_headerBottom);
}

void MENU_CREATEHEADER (char *text, char *destination)
{
	*destination = MENU_CHAR_HEADERTOP;
	*(destination+1) = MENU_CHAR_HEADERSTART;
	uint8_t foo;
	for(foo = 2; foo<MENU_HEADERWIDTH; foo++)
		*(destination+foo) = MENU_CHAR_HEADERTOP;
	for(foo = 2; (foo<MENU_HEADERWIDTH) && (*(text+foo-2) != 0); foo++)
		*(destination+foo) = *(text+foo-2);
	*(destination+foo) = MENU_CHAR_HEADERSTOP;
}

void MENU_DRAW (type_MENU_ENTRY **ArrayOfEntries, type_LCD *lcd, type_BUTTON *OKButton, type_ROTARYENC *selectEncoder, type_ROTARYENC *editEncoder)
{
	while(1)
	{
		MENU_LCDINIT(lcd);
		LCD_CLEAR(lcd);
		
		uint8_t numberOfEntries = 0;
		while(ArrayOfEntries[numberOfEntries])
		{
			numberOfEntries++;
		}
		
		
		selectEncoder->__value = 0;
		editEncoder -> __value = 0;
		editEncoder->accerelationFactor = ArrayOfEntries[0]->autoUpdateEncAccrl;
		selectEncoder->accerelationFactor = 200;
		int8_t selection = 0;
		int8_t reRender = True;
		uint16_t reRenderCounter = 0;
		uint16_t move = 0;
		int16_t editEncoder_rotation = 0;
		
		uint8_t doInit = False; 	// is done at this point
		while(!doInit)
		{
			_delay_ms(1);
			reRenderCounter++;
			if(reRenderCounter>=MENU_RERENDER_TIMEOUT)
				reRender = True;

			
			
			move = ROTARYENC_GET(selectEncoder);
			if(move)
			{
				selection += move;
				if(selection<0)
					selection = 0;
				if(selection>numberOfEntries-1)
					selection = numberOfEntries-1;
				
				if(editEncoder != None)	
					editEncoder->accerelationFactor = ArrayOfEntries[selection]->autoUpdateEncAccrl;
				reRender = True;
			}
			
			if(editEncoder != None)
				editEncoder_rotation = ROTARYENC_GET(editEncoder);
			if(editEncoder_rotation)
				reRender = True;
			
			if(reRender)
			{
				reRenderCounter = 0;
				//LCD_CLEAR(lcd);
				LCD_POS(lcd, 0, 0);
				if(ArrayOfEntries[selection]->numbering)
					LCD_INT(lcd, selection);
				
				if(ArrayOfEntries[selection]->selectable)
					LCD_WRITE(lcd, LCD_DATA, 0b01111110);	// ->
				else
					if(ArrayOfEntries[selection]->numbering)
						LCD_STRING(lcd, ":");
				
				if(ArrayOfEntries[selection]->autoUpdateText)
					ArrayOfEntries[selection]->autoUpdateHandler(ArrayOfEntries[selection]->text, editEncoder_rotation);
				LCD_STRING(lcd, ArrayOfEntries[selection]->text);
				LCD_STRING(lcd, "                ");
				if(selection == 0)
				{
					LCD_POS(lcd, 0, 15);
					LCD_WRITE(lcd, LCD_DATA, LCD_GC_CHAR3);	// StopUp
				}				
				if(selection > 0)
				{
					LCD_POS(lcd, 0, 15);
					LCD_WRITE(lcd, LCD_DATA, LCD_GC_CHAR1);	// ArrowUp
				}	
				
				
				if(selection+1 < numberOfEntries)
				{
					LCD_POS(lcd, 1, 0);
					if(ArrayOfEntries[selection+1]->numbering)
						LCD_INT(lcd, selection+1);
					
					if(ArrayOfEntries[selection+1]->numbering)
							LCD_STRING(lcd, ":");
					else
						if(ArrayOfEntries[selection+1]->selectable)
							LCD_STRING(lcd, " ");
					if(ArrayOfEntries[selection+1]->autoUpdateText)
						ArrayOfEntries[selection+1]->autoUpdateHandler(ArrayOfEntries[selection+1]->text, 0);
					LCD_STRING(lcd, ArrayOfEntries[selection+1]->text);
					LCD_STRING(lcd, "                ");
				}
				else
				{
					LCD_POS(lcd, 1, 0);
					for(uint8_t foo=0; foo<MENU_HEADERWIDTH; foo++)
						LCD_WRITE(lcd, LCD_DATA, MENU_CHAR_HEADERBOTTOM);

				}
				if(selection+1 < numberOfEntries)
				{
					LCD_POS(lcd, 1, 15);
					LCD_WRITE(lcd, LCD_DATA, LCD_GC_CHAR0);	// ArrowDown
				}
				if(selection+1 == numberOfEntries)
				{
					LCD_POS(lcd, 1, 15);
					LCD_WRITE(lcd, LCD_DATA, LCD_GC_CHAR2);	// StopDown
				}		
				reRender = False;				
			}
			
			if((BUTTON_GET(OKButton)) && (ArrayOfEntries[selection]->selectable))
			{
				if(ArrayOfEntries[selection]->selectHandler == MENU_EXIT)
					return;
				else
				{
					ArrayOfEntries[selection]->selectHandler();
					doInit = True;
				}
			}
			
		}
	}
}
