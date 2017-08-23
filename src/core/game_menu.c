/**
 * Game menu functions file
 *
 * @author Pierre HUBERT
 */

#include "../config.h"
#include "logging.h"
#include "game.h"
#include "game_started.h"
#include "ui.h"
#include "menu.h"

/**
 * Variables definition
 */
//static SDL_Renderer *renderer = NULL;
static Menu *menu = NULL;

/**
 * Display game menu
 */
void game_menu_display(){

    //Log action
    log_message(LOG_MESSAGE, "Display game menu");

    //Create menu if required
    if(menu == NULL){

        log_message(LOG_MESSAGE, "Create main game menu");

        //Allocate memory
        menu = malloc(sizeof(Menu));

        //Check for allocation error
        if(menu == NULL)
            fatal_error("Couldn't allocate memory for menu !");

        //Create menu
        *menu = menu_create(TEXTURE_MAIN_MENU);

        //Add menu options
        menu_add_option(menu, "Start game", 1);
        menu_add_option(menu, "Quit game", 2);
    }

    //Display the menu
    menu_display(menu);
}

/**
 * Handle game menu events
 *
 * @param SDL_Event *event The event to process
 */
void game_menu_handle_events(SDL_Event *event){

    //Determine the nature of the current event
    switch(event->type){

        //Check if it is a keyboard eventd
        case SDL_KEYDOWN:

            //The window will certainly need to be refreshed
            game_screen_to_update(1);

            switch(event->key.keysym.sym){

                //A : start the game
                case SDLK_a:
                game_started_start();
                break;

                //B : quit the application
                case SDLK_b:
                case SDLK_ESCAPE:
                game_quit();
                break;


            }
        break;

        //To quit the game
        case SDL_QUIT:
            //Change quit variable to true
            game_quit();
        break;

    }

}
