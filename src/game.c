/**
 * Game functions - Header file
 *
 * @author Pierre HUBERT
 */

#include "logging.h"
#include "ui.h"

/**
 * Initializate game
 */
void game_init(){

    //Inform about what is happening
    log_message(LOG_VERBOSE, "Initializating game...");

    //Initializate the SDL library
    ui_init();

    //Load the background
    ui_load_background();
    ui_display_background();

    //End of intialization
    return;
}

/**
 * Quit game
 */
void game_quit(){

    //Inform about what is happening
    log_message(LOG_VERBOSE, "Quitting game...");

    //Quit UI
    ui_quit();

}
