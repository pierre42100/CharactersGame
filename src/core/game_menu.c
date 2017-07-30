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

/**
 * Variables definition
 */
static SDL_Renderer *renderer = NULL;

/**
 * Display game menu
 */
void game_menu_display(){

    //Log action
    log_message(LOG_MESSAGE, "Display game menu");

    //Load menu texture if required
    if(ui_is_texture_loaded(TEXTURE_MENU) != 1)
        ui_load_image_into_texture(RES_DIRECTORY"menu.png", TEXTURE_MENU);

    //Get renderer
    renderer = ui_get_renderer();

    //Show menu
    SDL_SetRenderTarget(renderer, NULL);
    SDL_RenderCopy(renderer, ui_get_pointer_on_texture(TEXTURE_MENU), NULL, NULL);

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
