avr_ObjMenuLib
==============

This is a more object-orientated menu-library for AVR Microcontrollers written in C. It makes use of the linked libraries for buttons, rotary encoders and LC-displays.

This library consits of:

    MENUS.h
    MENUS.c

and offers:

    - handle infinite number of menu-layers with no duplicate code
    - automated and nice-looking scrolling
    - every menu entry can be one of the following kinds:
        - simple text
        - text, that is selectable (a normal menu entry)
        - text, that is automatically updated by a function of your choice -> you can make a list of editable variables
        - every of the above ones with additional automatic numbering (1:entry  2:entry  3:entry  etc.)
    - functions:
        MENU_CREATEHEADER: Give menu-title and get a fancy string (the menu title is simply a text-only-entry which shows this string)
        MENU_DRAW: Give this function a list of pointers to every menu-entry to draw the menu. Now you don't need to worry about anything, the microcontroller automaticall jumps in the right function when an entry is selected by the user

There are examples in main.c, which show the basics.

Note: At the moment, the library is written for two-lined displays, which means you can't configure the height of the menu-rendering. But you can adjust the columns in MENUS.h