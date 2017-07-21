/**
 * Game pause management - Source file
 *
 * @author Pierre HUBERT
 */

#include "config.h"
#include "logging.h"
#include "game.h"
#include "game_started.h"
#include "ui.h"

/**
 * Variables definition
 */
static SDL_Renderer *renderer = NULL;

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

    //Load menu texture if required
    if(ui_is_texture_loaded(TEXTURE_PAUSED_MENU) != 1)
        ui_load_image_into_texture(RES_DIRECTORY"paused-menu.png", TEXTURE_PAUSED_MENU);

    //Get renderer
    renderer = ui_get_renderer();

    //Show menu
    SDL_SetRenderTarget(renderer, NULL);
    SDL_RenderCopy(renderer, ui_get_pointer_on_texture(TEXTURE_PAUSED_MENU), NULL, NULL);

}

/**
 * Handle game menu events
 *
 * @param SDL_Event *event The event to process
 */
void game_paused_handle_events(SDL_Event *event){

    //Determine the nature of the current event
    switch(event->type){

        //Check if it is a keyboard eventd
        case SDL_KEYDOWN:

            //The window will certainly need to be refreshed
            game_screen_to_update(1);

            switch(event->key.keysym.sym){

                //ENTER : resume game
                case SDLK_RETURN:
                case SDLK_RETURN2:
                case SDLK_KP_ENTER:
                game_paused_resume();
                break;

                //ESCAPE : quit the application
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
