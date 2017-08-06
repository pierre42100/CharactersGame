#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

/**
 * Menu system - Header file
 *
 * @author Pierre HUBERT
 */

#include <SDL2/SDL.h>

/**
 * Menu object structure
 */
typedef struct Menu {


    //The texture that contains the menu
    SDL_Texture *texture;
} Menu;

#endif // MENU_H_INCLUDED
