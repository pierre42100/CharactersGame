/**
 * Game started functions file
 *
 * @author Pierre HUBERT
 */

#include <SDL2/SDL.h>

#include "lib/jsmn/jsmn.h"

#include "config.h"
#include "logging.h"
#include "ui.h"
#include "utils.h"
#include "main_character.h"
#include "character.h"
#include "game_started.h"
#include "game_paused.h"
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

    //Parse JSON file
    char json_file[] = "game.json";
    parse_game_json_file(json_file);

    //Update game state
    game_update_state(GAME_STATE_STARTED);

    //Inform the game is ready
    log_message(LOG_VERBOSE, "Game ready.");

    //End of intialization
    return;
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

                //Pause the game
                case SDLK_ESCAPE:
                case SDLK_p:
                    game_paused_pause();
                break;

                //Go back to the main menu
                //game_started_stop();
                //break;

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
 * Parse game JSON file
 *
 * @param const char *filename The name of the file to parse
 */
void parse_game_json_file(const char *filename){

    //Create required variables
    char *json_content = NULL;

    //Log action
    log_message(LOG_MESSAGE, "Parsing a game file");

    //Get the file content
    file_get_contents(&json_content, filename);

    puts(json_content);

    //Free memory
    free(json_content);
}
