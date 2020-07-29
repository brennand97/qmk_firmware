#include QMK_KEYBOARD_H

#include "led_timeout.h"

// Remember this is also the order of the layers!!
enum layout_names {
    _KL=0,       // Keys Layout: The main keyboard layout that has all the characters
    _MT,         // Mac Toggle: Flips the Ctrl and windows key when the windows key is pressed (good for shortcuts while keeping the windows key functional)
    _NL,         // Numpad Layout: Adds a 10-key number pad to the center of the board
    _FL,         // Function Layout: The function key activated layout with default functions and some added ones
};

enum custom_keycodes {
    // ctrl keycodes
    U_T_AUTO = SAFE_RANGE, //USB Extra Port Toggle Auto Detect / Always Active
    U_T_AGCR,              //USB Toggle Automatic GCR control
    DBG_TOG,               //DEBUG Toggle On / Off
    DBG_MTRX,              //DEBUG Toggle Matrix Prints
    DBG_KBD,               //DEBUG Toggle Keyboard Prints
    DBG_MOU,               //DEBUG Toggle Mouse Prints
    MD_BOOT,               //Restart into bootloader after hold timeout

    // led ctrl keycodes
    ROUT_TG,               // Timeout Toggle. Toggle idle LED time out on or off
    ROUT_VI,               // Timeout Value Increase. Increase idle time out before LED disabled
    ROUT_VD,               // Timeout Value Decrease. Decrease idle time out before LED disabled
    ROUT_FM,               // RGB timeout fast mode toggle
};

#define MT_MAC MT(MOD_LCTL, KC_LGUI)
