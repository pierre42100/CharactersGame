/**
 * UI utilities - Functions file
 *
 * @author Pierre HUBERT
 */

#include <SDL2/SDL.h>

#include "../config.h"
#include "logging.h"
#include "character.h"
#include "../characters/main_character.h"
#include "ui.h"
#include "ui_fonts.h"
#include "ui_utils.h"

extern SDL_Renderer *renderer;
extern SDL_Texture *textures[NUMBER_TEXTURES];

/**
 * Display UI loading message
 */
void ui_utils_display_loading_message(){

    //Declare variables
    UI_Text loading_msg;

    //Verbose message
    log_message(LOG_VERBOSE, "Display a loading message on the screen");

    //First, load background
    ui_display_background();

    //Create loading message texture if required
    if(textures[TEXTURE_LOADING_MSG] == NULL){

        //Create the texture
        ui_create_texture(TEXTURE_LOADING_MSG, WINDOW_WIDTH, WINDOW_HEIGHT, 1);

        //Create message object
        loading_msg = ui_font_create_variable("Loading, please wait...", 32);

        //Define target texture
        ui_font_set_target_texture(&loading_msg, textures[TEXTURE_LOADING_MSG]);

        //Update style
        ui_font_set_style(&loading_msg, FONT_STYLE_ITALIC);


        //Center message on the screen
        ui_font_set_coordinates(
            &loading_msg,
            (WINDOW_WIDTH-loading_msg.text_width)/2,
            (WINDOW_HEIGHT-loading_msg.text_height)/2
        );

        //Write message
        ui_font_write_texture(&loading_msg);

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

/**
 * Display the number of lives of the main character
 *
 * @return void
 */
void ui_utils_display_lives(){
    //Log message
    log_message(LOG_VERBOSE, "Display the number of lives of the character");

    //Get the number of lives of the main character
    int number_lives = main_character_get_lives();

    //Check if a texture for the number of lifes message already exist or not
    if(ui_is_texture_loaded(TEXTURE_LIFES_MESSAGE) != 1){

        //Create text message
        UI_Text lifes_msg = ui_font_create_variable("Lifes ", 14);
        ui_font_set_style(&lifes_msg, FONT_STYLE_BOLD);
        ui_font_set_coordinates(&lifes_msg, 0, 0);

        //Create the texture
        ui_create_texture(TEXTURE_LIFES_MESSAGE, lifes_msg.text_width, lifes_msg.text_height, 1);

        //Apply the message to the texture
        ui_font_set_target_texture(&lifes_msg, ui_get_pointer_on_texture(TEXTURE_LIFES_MESSAGE));
        ui_font_write_texture(&lifes_msg);

    }

    //Prepare rendering
    SDL_SetRenderTarget(renderer, NULL);

    //Apply life message on renderer
    int msg_width, msg_height;
    SDL_QueryTexture(ui_get_pointer_on_texture(TEXTURE_LIFES_MESSAGE), NULL, NULL, &msg_width, &msg_height);
    SDL_Rect target_area = {0, 0, msg_width, msg_height};
    if(SDL_RenderCopy(renderer, ui_get_pointer_on_texture(TEXTURE_LIFES_MESSAGE), NULL, &target_area) != 0)
        log_message(LOG_ERROR, "Couldn't render lifes message on the screen !");


    //Check if heart texture is already loaded or not
    if(ui_is_texture_loaded(TEXTURE_HEART) != 1)
        ui_load_image_into_texture(RES_DIRECTORY"heart.png", TEXTURE_HEART);

    //Retrieve informations about the heart texture
    int heart_w, heart_h;
    SDL_QueryTexture(ui_get_pointer_on_texture(TEXTURE_HEART), NULL, NULL, &heart_w, &heart_h);

    //Render the required number of heart
    for(int i = 1; i < number_lives; i++){

        //Defines the target area of the heart
        SDL_Rect heart_target_area = {msg_width + i*heart_w, 0, heart_w, heart_h};

        //Copy heart on renderer
        SDL_RenderCopy(renderer, ui_get_pointer_on_texture(TEXTURE_HEART), NULL, &heart_target_area);

    }

}
