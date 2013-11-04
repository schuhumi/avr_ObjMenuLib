#include <avr/io.h>
#include <string.h>
#include <stdlib.h> 	// dtostrf
#include "avr_ObjLcdLib/LCD.h"
#include "avr_ObjButtonLib/BUTTON.h"
#include "avr_ObjRotaryLib/ROTARYENC.h"
#include "MENUS.h"


/*		This menu-example creates a menu with the following structure:
 * 		
 * 		Menu
 * 		 + Entry 1
 * 		 + Entry 2
 * 		 + Entry 3
 * 		 + Entry 4
 * 		    + Entry 4_1
 * 			+ Entry 4_2
 * 			   + Edit Volt			<- editable
 * 			   + Edit Ampere		<- editable
 * 			+ Return
 */

void MainMenu (void);
void entry1 (void);
void entry2 (void);
void entry3 (void);
void entry4 (void);
void entry4_1 (void);
void entry4_2 (void);
void edit_Volt (char *text, int16_t rotation);
void edit_Ampere (char *text, int16_t rotation);
	
/// As soon as working with routines, it makes sense to make all the devices public
type_LCD frontLCD;
type_BUTTON button_A;
type_BUTTON button_B;
type_ROTARYENC encoder_A;
type_ROTARYENC encoder_B;

void RUN_THIS_EVERY_1MS (void)		// Without this the rotary encoders won't do anything
{
	ROTARYENC_RUN(&encoder_A);
	ROTARYENC_RUN(&encoder_B);
}

int main (void)
{	
	/// Configure Devices //////////////////////////////////////
	// Display configuration:
		frontLCD.ddr = &DDRD;
		frontLCD.port = &PORTD;
		frontLCD.pin = &PIND;
		frontLCD.pinNr_EN = PD5;
		frontLCD.pinNr_RS = PD4;
		frontLCD.pinNr_D4 = PD0;
		frontLCD.pinNr_D5 = PD1;
		frontLCD.pinNr_D6 = PD2;
		frontLCD.pinNr_D7 = PD3;

    // Buttion A configuration
		button_A.ddr = &DDRC;
		button_A.port = &PORTC;
		button_A.pin = &PINC;
		button_A.pinNr = PC7;
		button_A.internPullup = True;
		button_A.bounce_ms = 40;
		
	// Buttion B configuration
		button_B.ddr = &DDRC;
		button_B.port = &PORTC;
		button_B.pin = &PINC;
		button_B.pinNr = PC4;
		button_B.internPullup = True;
		button_B.bounce_ms = 40;	

    // Rotary encoder A  configuration
		encoder_A.ddr = &DDRC;
		encoder_A.port = &PORTC;
		encoder_A.pin = &PINC;
		encoder_A.pinNr_A = PC6;
		encoder_A.pinNr_B = PC5;
		encoder_A.internPullup = True;
		encoder_A.autoAcceleration = True;
		encoder_A.accerelationFactor = 200;
	
	// Rotary encoder B  configuration
		encoder_B.ddr = &DDRC;
		encoder_B.port = &PORTC;
		encoder_B.pin = &PINC;
		encoder_B.pinNr_A = PC3;
		encoder_B.pinNr_B = PC2;
		encoder_B.internPullup = True;
		encoder_B.autoAcceleration = True;
		encoder_B.accerelationFactor = 100;
	/// END Configure Devices //////////////////////////////////
	
	/// INIT Devices ///////////////////////////////////////////
	// INIT display
		LCD_INIT(&frontLCD);
		LCD_CLEAR(&frontLCD);

    // INIT buttons	
		BUTTON_INIT(&button_A);
		BUTTON_INIT(&button_B);

    // INIT rotary encoders
		ROTARYENC_INIT(&encoder_A);
		ROTARYENC_INIT(&encoder_B);		
	/// END INIT Devices ///////////////////////////////////////
	
	while(1)
        MainMenu(); // Enter main-menu (see below)

	return 0;
}


/// MAIN MENU START ////////////////////////////////////////
void MainMenu (void)
{
	char headertxt[MENU_HEADERWIDTH];
	
	//                 "Text", save in
	MENU_CREATEHEADER ("Menu", headertxt);
	
	type_MENU_ENTRY		MainMenu_Name;
	MainMenu_Name.text = headertxt;			
	MainMenu_Name.selectable = False;		    // Not clickable, since its the name of the menu
	MainMenu_Name.numbering = False;
	MainMenu_Name.autoUpdateText = False;
	
	type_MENU_ENTRY		MainMenu_Entry1;	    // Name of entry
	MainMenu_Entry1.text = "Entry 1";		    // Text to show
	MainMenu_Entry1.selectable = True;     		// User can click on it
	MainMenu_Entry1.numbering = True;			// Use auto-numbering
	MainMenu_Entry1.selectHandler = entry1;	// Routine to call, when entry is clicked
	MainMenu_Entry1.autoUpdateText = False;		// Routine to call, to automatically update displayed text
	
	type_MENU_ENTRY		MainMenu_Entry2;
	MainMenu_Entry2.text = "Entry 2";
	MainMenu_Entry2.selectable = True;
	MainMenu_Entry2.numbering = True;
	MainMenu_Entry2.selectHandler = entry2;
	MainMenu_Entry2.autoUpdateText = False;
	
	type_MENU_ENTRY		MainMenu_Entry3;
	MainMenu_Entry3.text = "Entry 3";
	MainMenu_Entry3.selectable = True;
	MainMenu_Entry3.numbering = True;
	MainMenu_Entry3.selectHandler = entry3;
	MainMenu_Entry3.autoUpdateText = False;
	
	type_MENU_ENTRY		MainMenu_Entry4;
	MainMenu_Entry4.text = "Entry 4";
	MainMenu_Entry4.selectable = True;
	MainMenu_Entry4.numbering = True;
	MainMenu_Entry4.selectHandler = entry4;
	MainMenu_Entry4.autoUpdateText = False;
	
	type_MENU_ENTRY *MainMenu[6];
	MainMenu[0] = &MainMenu_Name;
	MainMenu[1] = &MainMenu_Entry1;
	MainMenu[2] = &MainMenu_Entry2;
	MainMenu[3] = &MainMenu_Entry3;
	MainMenu[4] = &MainMenu_Entry4;
	MainMenu[5] = MENU_END;
	
	//        List of Entries, &display , &select-button, &select-encoder, &editEncoder
	MENU_DRAW(MainMenu       , &frontLCD, &button_A     , &encoder_A     , None        );
	
}
/// MAIN MENU END //////////////////////////////////////////

/// MAIN ENTRIES ////////////////////////////////////////////////
void entry1 (void)
{
    // Do whatever has to be done, you can create a sub-menu
}

void entry2 (void)
{
    // Do whatever has to be done, you can create a sub-menu
}

void entry3 (void)
{
    // Do whatever has to be done, you can create a sub-menu
}

void entry4 (void)
{
    // Example for sub-menu
	char headertxt[MENU_HEADERWIDTH];
	MENU_CREATEHEADER ("Entry4-Menu", headertxt);
	
	type_MENU_ENTRY		Entry4Menu_Name;
	Entry4Menu_Name.text = headertxt;
	Entry4Menu_Name.selectable = False;
	Entry4Menu_Name.numbering = False;
	Entry4Menu_Name.autoUpdateText = False;
	
	type_MENU_ENTRY		Entry4Menu_Entry1;
	Entry4Menu_Entry1.text = "Entry 4_1";
	Entry4Menu_Entry1.selectable = True;
	Entry4Menu_Entry1.numbering = True;
	Entry4Menu_Entry1.selectHandler = entry4_1;
	Entry4Menu_Entry1.autoUpdateText = False;
	
	type_MENU_ENTRY		Entry4Menu_Entry2;
	Entry4Menu_Entry2.text = "Entry_4_2";
	Entry4Menu_Entry2.selectable = True;
	Entry4Menu_Entry2.numbering = True;
	Entry4Menu_Entry2.selectHandler = entry4_2;
	Entry4Menu_Entry2.autoUpdateText = False;

	type_MENU_ENTRY		Entry4Menu_Exit;
	Entry4Menu_Exit.text = "Return";
	Entry4Menu_Exit.selectable = True;
	Entry4Menu_Exit.numbering = True;
	Entry4Menu_Exit.selectHandler = MENU_EXIT;
	Entry4Menu_Exit.autoUpdateText = False;
	
	type_MENU_ENTRY *Entry4Menu[5];
	Entry4Menu[0] = &Entry4Menu_Name;
	Entry4Menu[1] = &Entry4Menu_Entry1;
	Entry4Menu[2] = &Entry4Menu_Entry2;
	Entry4Menu[3] = &Entry4Menu_Exit;
	Entry4Menu[4] = MENU_END;
	
	MENU_DRAW(Entry4Menu, &frontLCD, &button_A, &encoder_A, None);
}
/// END MAIN ENTRIES ////////////////////////////////////////////

/// SUBMENU 4 ENTRIES ////////////////////////////////////////////////
void entry4_1 (void)
{
    // Do whatever has to be done, you can create a sub-sub-menu
    // (and then a sub-sub-sub-menu and so on)
}

void entry4_2 (void)
{
    // Example for sub-sub-menu, that has editable variables as entries:
	char headertxt[MENU_HEADERWIDTH];
	
	MENU_CREATEHEADER ("Edit these:", headertxt);
	
	type_MENU_ENTRY		Entry42Menu_Name;
	Entry42Menu_Name.text = headertxt;			
	Entry42Menu_Name.selectable = False;		
	Entry42Menu_Name.numbering = False;
	Entry42Menu_Name.autoUpdateText = False;
	
	char txt_Volt[MENU_HEADERWIDTH] = "Volt:";          // String for name of entry
	type_MENU_ENTRY		Entry42Menu_Entry1;	                // Create Entry
	Entry42Menu_Entry1.text = txt_Volt;	                    // Set string as name of entry
	Entry42Menu_Entry1.selectable = False;                  // User can't click on it
	Entry42Menu_Entry1.numbering = False;                   // Disable numbering
	Entry42Menu_Entry1.autoUpdateText = True;               // Displayed text of entry (=Value) is automatically updated...
	Entry42Menu_Entry1.autoUpdateHandler = edit_Volt;       // ...from this sub-program (it gets the "edit-encoder"-value and a pointer to the string to modify it)
	Entry42Menu_Entry1.autoUpdateEncAccrl = 200;		    // Encoderaccerelation for "edit-encoder"
	
	char txt_Ampere[MENU_HEADERWIDTH] = "Ampere:";
	type_MENU_ENTRY		Entry42Menu_Entry2;
	Entry42Menu_Entry2.text = txt_Ampere;
	Entry42Menu_Entry2.selectable = False;
	Entry42Menu_Entry2.numbering = False;
	Entry42Menu_Entry2.autoUpdateText = True;
	Entry42Menu_Entry2.autoUpdateHandler = edit_Ampere;
	Entry42Menu_Entry2.autoUpdateEncAccrl = 100;
	
	type_MENU_ENTRY		Entry42Menu_Exit;
	Entry42Menu_Exit.text = "Return";
	Entry42Menu_Exit.selectable = True;
	Entry42Menu_Exit.numbering = False;
	Entry42Menu_Exit.selectHandler = MENU_EXIT;
	Entry42Menu_Exit.autoUpdateText = False;
	
	type_MENU_ENTRY *Entry42Menu[5];
	Entry42Menu[0] = &Entry42Menu_Name;
	Entry42Menu[1] = &Entry42Menu_Entry1;
	Entry42Menu[2] = &Entry42Menu_Entry2;
    Entry42Menu[3] = &Entry42Menu_Exit;
	Entry42Menu[4] = MENU_END;
	
	//        List of Entries, &display , &select-button, &select-encoder, &editEncoder
	MENU_DRAW(Entry42Menu    , &frontLCD, &button_A     , &encoder_A     , &encoder_B   );
}	
/// END SUBMENU 4 ENTRIES ////////////////////////////////////////////////

/// SUBSUBMENU 4_2 ENTRIES ///////////////////////////////////////////////
void edit_Volt (char *text, int16_t rotation)
{
	static float voltage = 0;                           // static ->   =0 is only set once, no matter how often routine is being called

	voltage += (float)rotation/10;                      // apply rotation (which is done in the menu with the "edit-encoder" to the variable 
	
	char string_voltage[8];                             // create a string to save the voltage in
	dtostrf(voltage,1,3,string_voltage);                // write the voltage in the string (x.xxx)

	char tmp_text[MENU_HEADERWIDTH] = "Voltage:";       // temporarily create string to work with and write "Voltage:" in it
	strcat(tmp_text, string_voltage);                   // append the voltage-string on it
	strcat(tmp_text, "V");                              // append a "V" for "Volt"
	strcpy(text, tmp_text);                             // copy the working-string to the string that is displayed in the menu
}

void edit_Ampere (char *text, int16_t rotation)     
{
	static float ampere = 0;                   
                                                 
	ampere += (float)rotation/100;              
	                                             
	char string_ampere[8];                      
	dtostrf(ampere,1,3,string_ampere);           
                                                 
	char tmp_text[MENU_HEADERWIDTH] = "Ampere:";
	strcat(tmp_text, string_ampere);             
	strcat(tmp_text, "A");                       
	strcpy(text, tmp_text);                      
}

/// END SUBSUBMENU 4_2 ENTRIES ///////////////////////////////////////////
