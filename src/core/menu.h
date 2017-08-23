#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

/**
 * Menu system - Header file
 *
 * @author Pierre HUBERT
 */

#include <SDL2/SDL.h>

//The maximum number of menu entries
#define MENU_MAXIMUM_OPTIONS 5
#define MENU_MIN_POS_X 320
#define MENU_MIN_POS_Y 220

/**
 * Menu entry structure
 */
typedef struct Menu_Entry {
    //The full name of the option
    char *name;

    //The value of the option
    int value;
} Menu_Entry;

/**
 * Menu object structure
 */
typedef struct Menu {

    //The options of the menu
    Menu_Entry *options[MENU_MAXIMUM_OPTIONS];
    int number_options;

    //Currently selected option
    int curr_option;

    //The texture that contains the menu
    int texture_number;
} Menu;

/**
 * Create a new menu
 *
 * @param int texture_number The number of the texture in main texture array
 */
Menu menu_create(int texture_number);

/**
 * Add a new menu option
 *
 * @param Menu *menu The target menu
 * @param const char *name Option name
 * @param int value Value of the option
 */
void menu_add_option(Menu *menu, const char *name, int value);

/**
 * Initialize the texture of the menu
 *
 * @param Menu *menu The menu with the texture to initializate
 */
void menu_init_texture(Menu *menu);

/**
 * Display a menu
 *
 * @param Menu *menu The menu to display
 */
void menu_display(Menu *menu);

#endif // MENU_H_INCLUDED
