#ifndef UI_UTILS_H_INCLUDED
#define UI_UTILS_H_INCLUDED

/**
 * UI utilities - Header file
 *
 * @author Pierre HUBERT
 */

#include "character.h"

/**
 * Display UI loading message
 */
void ui_utils_display_loading_message();

/**
 * Display a character
 *
 * @param Character character The character to display
 * @return void (Fatal error in case of failure)
 */
void character_display(Character *character);

#endif // UI_UTILS_H_INCLUDED
