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

/**
 * Menu object structure
 */
typedef struct Menu {

    //The options of the menu
    char *options[MENU_MAXIMUM_OPTIONS];
    int number_options;

    //Currently selected option
    int curr_option;

    //The texture that contains the menu
    int texture_number;
} Menu;

/**
 * Create a new menu
 *
 * @param const char *options Options of the menu
 * @param int texture_number The number of the texture in main texture array
 */
Menu menu_create(const char *options[], int texture_number);

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
