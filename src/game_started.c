/**
 * Game started functions file
 *
 * @author Pierre HUBERT
 */

#include <SDL2/SDL.h>

#include "config.h"
#include "logging.h"
#include "ui.h"
#include "main_character.h"
#include "character.h"
#include "game_started.h"
#include "game.h"

/**
 * Start the game
 */
void game_started_start(){

    //Display loading message
    ui_display_loading_message();

    //Refresh screen
    ui_refresh_window();

    //Load main character
    main_character_create();

    //Update game state
    game_update_state(GAME_STATE_STARTED);

    //Inform the game is ready
    log_message(LOG_VERBOSE, "Game ready.");

    //End of intialization
    return;
}

/**
 * Handle game started events
 *
 * @param SDL_Event *event The event to process
 */
void game_started_handle_events(SDL_Event *event){
    //Determine the nature of the current event
    switch(event->type){

        //Check if it is a keyboard eventd
        case SDL_KEYDOWN:

            //The window will certainly need to be refreshed
            game_screen_to_update(1);

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


                //Go back to the main menu
                case SDLK_ESCAPE:
                game_started_stop();
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

/**
 * Update game started window
 */
void game_started_refresh_window(){
    //Display the main character
    main_character_display();
}

/**
 * Stop the current game
 */
void game_started_stop(){

    //Log action
    log_message(LOG_VERBOSE, "Stopping game.");

    //Destroy main character
    main_character_destroy();

    //Update game state
    game_update_state(GAME_STATE_MENU);

}
