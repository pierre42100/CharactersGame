/**
 * Game pause management - Source file
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
static Menu *menu = NULL;

/**
 * Makes game pause
 */
void game_paused_pause(){

    //Update game state
    game_update_state(GAME_STATE_PAUSED);

    //Need the screen to be updated
    game_screen_to_update(1);

}

/**
 * Resume the game
 */
void game_paused_resume(){
    //Update game state
    game_update_state(GAME_STATE_STARTED);

    //Need the screen to be updated
    game_screen_to_update(1);
}

/**
 * Display game menu
 */
void game_paused_display(){

    //Log action
    log_message(LOG_MESSAGE, "Display game paused menu");

    //Check if game paused menu has to be initializated
    if(menu == NULL){

        log_message(LOG_MESSAGE, "Create game paused menu");

        //Allocate memory
        menu = malloc(sizeof(Menu));

        //Check for allocation error
        if(menu == NULL)
            fatal_error("Couldn't allocate memory for menu !");

        //Create menu
        *menu = menu_create(TEXTURE_PAUSED_MENU, "Paused game");

        //Add menu options
        menu_add_option(menu, "Resume game", 1);
        menu_add_option(menu, "Quit game", 2);

    }

    menu_display(menu);


}

/**
 * Handle game menu events
 *
 * @param SDL_Event *event The event to process
 */
void game_paused_handle_events(SDL_Event *event){

    //Make menu component handles event
    int action = menu_handle_event(menu, event);

    //Check what to do
    switch(action){

        //Resume game
        case 1:
            game_paused_resume();
        break;

        //Stop game
        case 2:
            game_started_stop();
        break;
    }
}
