#include QMK_KEYBOARD_H

enum layout_names {
    _KL=0,       // Keys Layout: The main keyboard layout that has all the characters
    _FL,         // Function Layout: The function key activated layout with default functions and some added ones
    _NL,         // Numpad Layout: Adds a 10-key number pad to the center of the board
};

enum ctrl_keycodes {
    U_T_AUTO = SAFE_RANGE, //USB Extra Port Toggle Auto Detect / Always Active
    U_T_AGCR,              //USB Toggle Automatic GCR control
    DBG_TOG,               //DEBUG Toggle On / Off
    DBG_MTRX,              //DEBUG Toggle Matrix Prints
    DBG_KBD,               //DEBUG Toggle Keyboard Prints
    DBG_MOU,               //DEBUG Toggle Mouse Prints
    MD_BOOT,               //Restart into bootloader after hold timeout
};

// enum custom_keycodes {
//     TG_MAC = MD_BOOT + 1 // This should always be the last enum from ctrl_keycodes + 1
// }
