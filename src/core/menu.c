/**
 * Menu system - Source file
 *
 * @author Pierre Hubert
 */

#include <SDL2/SDL.h>

#include "logging.h"
#include "menu.h"

/**
 * Create a new menu
 *
 * @param const char[] options Options of the menu
 */
Menu menu_create(const char *options){

    //Create menu object
    Menu menu;

    //Initialize options
    menu.curr_option = 0;

    for(int i = 0; i < MENU_MAXIMUM_OPTIONS; i++){

        //Check if current entry could be useful
        if(strlen(&options[i]) < 2)
            break; //End of initialization

        //Copy entry in options array
        menu.options[i] = NULL;
        menu.options[i] = malloc(sizeof(char)*strlen(&options[i]));

        //Check for allocation erro
        if(menu.options[i] == NULL)
            fatal_error("Couldn't allocate memory !");

        //Copy menu option in array
        strcpy(menu.options[i], &options[i]);

    }

    //Return result
    return menu;

}
