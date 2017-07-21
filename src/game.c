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
#include "character.h"
#include "game.h"

//This variables defines if the game has to be left or not
static int quit_game = 0;

//This variable stores when a window refreshing is required
static int need_window_refresh = 1;

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

        //Handle event
        game_handle_event(&event);

        //Check if we have to quit game
        if(quit_game == 1){
            //Inform user
            log_message(LOG_MESSAGE, "A request has been made to quit the game.");

            break;
        }

        //Check if it is required to refresh screen
        if(need_window_refresh == 1){
            game_refresh_screen();
            need_window_refresh = 0;
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
 * Handle game events
 *
 * @param SDL_Event *event The event to handles
 */
void game_handle_event(SDL_Event *event){
    //Determine the nature of the current event
    switch(event->type){

        //Check if it is a keyboard eventd
        case SDL_KEYDOWN:

            //The window will certainly need to be refreshed
            need_window_refresh = 1;

            switch(event->key.keysym.sym){

                //To go right
                case SDLK_RIGHT:
                case SDLK_d:
                    main_character_move(MOVE_CHARACTER_RIGHT);
                break;

                //To go left
                case SDLK_LEFT:
                case SDLK_q:
                    main_character_move(MOVE_CHARACTER_LEFT);
                break;

                //To go up
                case SDLK_UP:
                case SDLK_z:
                    main_character_move(MOVE_CHARACTER_UP);
                break;

                //To go down
                case SDLK_DOWN:
                case SDLK_w:
                    main_character_move(MOVE_CHARACTER_DOWN);
                break;



            }
        break;

        //To quit the game
        case SDL_QUIT:
            //Change quit variable to true
            quit_game = 1;
        break;

    }

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
