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
#include "game_editor.h"
#include "game_menu.h"

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
        *menu = menu_create(TEXTURE_MAIN_MENU, "Main menu");

        //Add menu options
        menu_add_option(menu, "Start game", MENU_OPTION_START_GAME);
        menu_add_option(menu, "Map editor", MENU_OPTION_EDITOR);
        menu_add_option(menu, "Quit game", MENU_OPTION_QUIT_GAME);
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

    int action = menu_handle_event(menu, event);

    //Check what to do now
    switch(action){

        //Start game
        case MENU_OPTION_START_GAME:
            game_started_start();
        break;

        //Game editor
        case MENU_OPTION_EDITOR:
            game_editor_open();
        break;

        //Quit game
        case MENU_OPTION_QUIT_GAME:
            game_quit();
        break;
    }
}
