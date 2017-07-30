/**
 * Game over functions file
 *
 * Handles actions when the user loses its game
 *
 * @author Pierre HUBERT
 */

#include <SDL2/SDL.h>

#include "../config.h"

#include "ui.h"
#include "logging.h"
#include "game.h"
#include "game_started.h"
#include "game_over.h"

/**
 * Enter into game over mode
 */
void game_over_enter(){

    //Stop the game
    game_started_stop();

    //Change game mode
    game_update_state(GAME_STATE_OVER);

    //The screen needs to be refreshed
    game_screen_to_update(1);
}

/**
 * Display the game over screen
 */
void game_over_display(){

    //Declare variables
    SDL_Renderer *renderer = NULL;

    //Informations about the game over texture
    int texture_w = 0;
    int texture_h = 0;
    SDL_Texture *texture = NULL;


    log_message(LOG_VERBOSE, "Display game over screen...");

    //Load game over icon
    if(ui_is_texture_loaded(TEXTURE_GAME_OVER) != 1)
        ui_load_image_into_texture(RES_DIRECTORY"game_over.png", TEXTURE_GAME_OVER);

    //Get the current renderer
    renderer = ui_get_renderer();
    if(renderer == NULL){
        fatal_error("Couldn't retrieve renderer in order to display game over menu !");
    }

    //Retrieve texture
    texture = ui_get_pointer_on_texture(TEXTURE_GAME_OVER);
    if(texture == NULL){
        fatal_error("Couldn't get informations about the texture !");
    }

    //Get game over texture informations
    if(SDL_QueryTexture(texture, NULL, NULL, &texture_w, &texture_h) != 0)
        fatal_error("Couldn't query fatal error texture !");

    //Copy game over texture into renderer
    SDL_Rect texture_dest = {(WINDOW_WIDTH-texture_w)/2, (WINDOW_HEIGHT-texture_h)/2, texture_w, texture_h};
    SDL_SetRenderTarget(renderer, NULL);
    SDL_RenderCopy(renderer, texture, NULL, &texture_dest);

}

/**
 * Quit game over mode
 */
void game_over_quit(){

    //Update game state
    game_update_state(GAME_STATE_MENU);

    //Need screen refresh
    game_screen_to_update(1);

}

/**
 * Handle game over state events
 *
 * @param SDL_Event *event The event to process
 */
void game_over_handles_events(SDL_Event *event){

    //Process events
    switch(event->key.keysym.sym){

        //To go back to the main menu
        case SDLK_ESCAPE:
        case SDLK_RETURN:
        case SDLK_RETURN2:
        case SDLK_KP_ENTER:
            game_over_quit();
        break;


    }
}
