/**
 * UI utilities - Functions file
 *
 * @author Pierre HUBERT
 */

#include <SDL2/SDL.h>

#include "../config.h"
#include "logging.h"
#include "character.h"
#include "ui.h"
#include "ui_fonts.h"
#include "ui_utils.h"

extern SDL_Renderer *renderer;
extern SDL_Texture *textures[NUMBER_TEXTURES];

/**
 * Display UI loading message
 */
void ui_utils_display_loading_message(){

    //Verbose message
    log_message(LOG_VERBOSE, "Display a loading message on the screen");

    //First, load background
    ui_display_background();

    //Create loading message texture if required
    if(textures[TEXTURE_LOADING_MSG] == NULL){

        //Create the texture
        ui_create_texture(TEXTURE_LOADING_MSG, WINDOW_WIDTH, WINDOW_HEIGHT, 1);

        //Prepare text rendering
        char message[] = "Loading, please wait...";
        int message_style = FONT_STYLE_NORMAL;
        int message_rendering = FONT_RENDERING_SOLID;
        int message_height = 30;
        int message_width = 0;

        //Compute given informations
        ui_font_determine_text_size(message, message_style, &message_width, message_height);

        //Determine message coordinates
        int message_x = (WINDOW_WIDTH-message_width)/2;
        int message_y = (WINDOW_HEIGHT-message_height)/2;
        //Write a text on the picture
        ui_font_write_texture(textures[TEXTURE_LOADING_MSG], message, ui_get_color(UI_COLOR_WHITE), message_x, message_y, message_height, message_style, message_rendering);

    }

    //Update rendering target
    SDL_SetRenderTarget(renderer, NULL);

    //Prepare message copy
    //Get informations about the texture
    int msg_width, msg_height;
    SDL_QueryTexture(textures[TEXTURE_LOADING_MSG], NULL, NULL, &msg_width, &msg_height);

    //Define destination AREA
    SDL_Rect target_area = {(WINDOW_WIDTH-msg_width)/2, (WINDOW_HEIGHT-msg_height)/2, msg_width, msg_height};

    //Copy texture
    SDL_RenderCopy(renderer, textures[TEXTURE_LOADING_MSG], NULL, &target_area);

    //Refresh the screen
    ui_refresh_window();
}

/**
 * Display a character
 *
 * @param Character character The character to display
 * @return void (Fatal error in case of failure)
 */
void character_display(Character *character){

    //Set right render target
    SDL_SetRenderTarget(renderer, NULL);

    //Prepare the application
    SDL_Rect target_area = {
        //Position of the character
        character->pos_x*GAME_CELL_WIDTH + GAME_GRID_X_POSITION,
        character->pos_y*GAME_CELL_HEIGHT + GAME_GRID_Y_POSITION,

        //Size of the character
        character->w*GAME_CELL_WIDTH,
        character->h*GAME_CELL_HEIGHT
    };

    //Apply character
    SDL_RenderCopy(renderer, character->texture, NULL, &target_area);

}
