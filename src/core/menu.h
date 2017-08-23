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

    //Currently selected option
    int curr_option;

    //The texture that contains the menu
    SDL_Texture *texture;
} Menu;

/**
 * Create a new menu
 *
 * @param const char[] *options Options of the menu
 */
Menu menu_create(const char *options);

#endif // MENU_H_INCLUDED
