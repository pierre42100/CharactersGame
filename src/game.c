/**
 * Game functions - Header file
 *
 * @author Pierre HUBERT
 */

#include <SDL2/SDL.h>
#include "logging.h"
#include "ui.h"
#include "config.h"
#include "main_character.h"
#include "game.h"

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

    //Display loading message
    ui_display_loading_message();

    //Load main character
    main_character_create();

    //Inform the game is ready
    log_message(LOG_VERBOSE, "Game ready.");

    //End of intialization
    return;
}

/**
 * Game loop (handles events happening during the game and process them)
 */
void game_loop(){

    //Inform about what is happening
    log_message(LOG_VERBOSE, "Starting game loop...");

    //Refresh game screen
    game_refresh_screen();

    //Event handler
    SDL_Event event;

    //Perpetual loop
    while(1==1){
        //Wait for an event
        SDL_WaitEvent(&event);

        //Determine the nature of the current event
        switch(event.type){

            //To quit the game
            case SDL_QUIT:
                return; //Quit function
            break;

        }

    }

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


/**
 * Refresh game screen
 */
void game_refresh_screen(){

    //Display game background
    ui_display_background();

    //Display the main character
    main_character_display();

    //Refresh the screen
    ui_refresh_window();

}
