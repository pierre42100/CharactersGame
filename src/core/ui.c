/**
 * UI functions - Source file
 *
 * This file handle the main graphical operations
 *
 * @author Pierre HUBERT
 */

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "logging.h"
#include "../config.h"
#include "ui.h"
#include "ui_fonts.h"

/**
 * Variables definition
 */
static SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
SDL_Texture *textures[NUMBER_TEXTURES];


/**
 * Initializate the SDL library plus create programm windows & renderer
 */
void ui_init(){

    //Initializate SDL
    if(SDL_Init(SDL_INIT_VIDEO) != 0)
        fatal_error("Couldn't initializate the SDL2.0 Library !");


    //Create window
    window = SDL_CreateWindow(GAME_NAME, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);

    //Check if the window was successfully created
    if(window == NULL)
        fatal_error("Couldn't create programm window !");

    //Create renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    //Check if the operation failed
    if(renderer == NULL){
        log_message(LOG_ERROR, "Couldn't create a renderer based on accelarated way. Falling back to software renderer.");
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    }

    //Check if not any renderer could be created
    if(renderer == NULL){
        //This time it is a fatal error
        fatal_error("Couldn't create a renderer (tryed both accelerated & software renderer) !");
    }

    //Initializate TTF library
    ui_font_init(FONT_FILE, FONT_PTSIZE);

    //End of function
    return;
}

/**
 * Terminate and close UI
 */
void ui_quit(){

    //Message
    log_message(LOG_VERBOSE, "Terminate UI.");

    //Quit TTF Library
    ui_font_quit();

    //Destroy all textures
    for(int i = 0; i < NUMBER_TEXTURES; i++){
        //Destroy the texture only if it exists
        if(textures[i] != NULL){
            SDL_DestroyTexture(textures[i]);
        }

    }

    //Destroy renderer (if it exists)
    if(renderer != NULL)
        SDL_DestroyRenderer(renderer);

    //Destroy window (if it exists)
    if(window != NULL){
        SDL_DestroyWindow(window);
    }

    //Quit SDL
    SDL_Quit();

    //End of function
    return;
}

/**
 * Set the window icon
 *
 * @param const char *filename The name of the image to use as an icon
 */
void ui_set_window_icon(const char *filename){

    //Verbose message
    log_message(LOG_VERBOSE, "Setting window icon.");

    //Create required variables
    SDL_Surface *image = NULL;

    image = IMG_Load(filename);

    //Check for errors
    if(image == NULL)
        fatal_error("Couldn't load required image ! (to use as programm icon)");

    //Set window icon
    SDL_SetWindowIcon(window, image);

    //Free memory
    SDL_FreeSurface(image);

}

/**
 * Refresh the window
 */
void ui_refresh_window(){
    SDL_RenderPresent(renderer);
}

/**
 * Load an image and save it in a texture
 *
 * @param const char *filename The name of the image to load
 * @param int target_texture The target texture of the image
 * @return void (Fatal error in case of failure)
 */
void ui_load_image_into_texture(const char *filename, int target_texture){

    //Log action
    log_message(LOG_VERBOSE, "Loading an image");

    //Declare variables
    SDL_Surface *image = NULL;

    //Load image
    image = IMG_Load(filename);

    //Check an error
    if(image == NULL){
        fatal_error("Couldn't load required image !");
    }

    //Copy the image into the desired texture
    textures[target_texture] = SDL_CreateTextureFromSurface(renderer, image);

    //Free memory
    SDL_FreeSurface(image);

    //Check for errors
    if(textures[target_texture] == NULL)
        fatal_error("Couldn't copy a surface into a texture !");

}


/**
 * Create a texture in the array of textures and return it as result
 *
 * @param int target_texture The target texture
 * @param int w
 * @param int h > Coordinates of the texture
 * @param int force Force the texture to be created (destroy any previous texture)
 */
SDL_Texture* ui_create_texture(int target_texture, int w, int h, int force){

    //Check if the texture already exists or not
    if(textures[target_texture] != NULL){
        //Check if we have to skip operation
        if(force == 0)
            return textures[target_texture];

        //Else we destroy the texture
        SDL_DestroyTexture(textures[target_texture]);

        //Security
        textures[target_texture] = NULL;
    }

    //Create the texture
    textures[target_texture] = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, w, h);

    //Check for errors
    if(textures[target_texture] == NULL)
        fatal_error("Couldn't create required texture !");

    //Set texture blend mode
    if(SDL_SetTextureBlendMode(textures[target_texture], SDL_BLENDMODE_BLEND) != 0)
        fatal_error("Coudnt't set blend mode for newly created texture !");

    //Return newly created texture
    return textures[target_texture];

}

/**
 * Check if a texture was loaded or not
 *
 * @param int texture_number The number of the texture to check
 * @return int 1 = yes / 0 = no
 */
int ui_is_texture_loaded(int texture_number){
    return textures[texture_number] == NULL ? 0 : 1;
}

/**
 * Destroy a specified texture
 *
 * @param int texture_number The texture to destroy
 */
void ui_destroy_texture(int texture_number){
    SDL_DestroyTexture(textures[texture_number]);
}

/**
 * Get the pointer on the renderer
 *
 * @return SDL_Renderer *renderer Pointer on renderer
 */
SDL_Renderer* ui_get_renderer(){

    return renderer;

}

/**
 * Get the pointer on a texture entry
 *
 * @param int texture_number The number of the texture to get
 * @return SDL_Texture* Pointer on the desired texture
 */
SDL_Texture* ui_get_pointer_on_texture(int texture_number){

    return textures[texture_number];

}

/**
 * Load game background into a texture
 */
void ui_load_background(){

    //Check if grass texture has to be loaded
    if(textures[TEXTURE_GRASS] == NULL)
        ui_load_image_into_texture(RES_DIRECTORY"grass.png", TEXTURE_GRASS);

    //Retrieve informations about the texture
    int grass_width, grass_height;
    SDL_QueryTexture(textures[TEXTURE_GRASS], NULL, NULL, &grass_width, &grass_height);

    //Check if background texture exists or not
    if(textures[TEXTURE_BACKGROUND] == NULL){
        //Create it
        textures[TEXTURE_BACKGROUND] = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, WINDOW_WIDTH, WINDOW_HEIGHT);

        if(textures[TEXTURE_BACKGROUND] == NULL){
            //Then this is a fatal error
            fatal_error("Couldn't create the background texture !");
        }
    }

    //Set the texture as the rendering target
    SDL_SetRenderTarget(renderer, textures[TEXTURE_BACKGROUND]);

    //Fill the texture with the background
    for(int i = 0; i<WINDOW_WIDTH; i += grass_width){
        for(int j = 0; j < WINDOW_HEIGHT; j += grass_height){

            //Copy the grass texture into the texture
            SDL_Rect dest_area = {i, j, grass_width, grass_height};

            if(SDL_RenderCopy(renderer, textures[TEXTURE_GRASS], NULL, &dest_area) != 0)
                log_message(LOG_ERROR, "Couldn't copy a piece of grass on the background !"); //Handle errors

        }
    }

    //Change rendering target
    SDL_SetRenderTarget(renderer, NULL);

    //End of function
    return;

}

/**
 * Display the background on the screen (clean it)
 */
void ui_display_background(){

    //Change rendering target
    SDL_SetRenderTarget(renderer, NULL);

    //Display the bakcground
    SDL_RenderCopy(renderer, textures[TEXTURE_BACKGROUND], NULL, NULL);

}


/**
 * Colors functions
 */

/**
 * Get a specific color
 *
 * @param int color The color to get
 * @return SDL_Color The required color
 */
SDL_Color ui_get_color(int color){

    //Declare variables
    SDL_Color result_color;

    switch(color){

        case UI_COLOR_WHITE:
            result_color.r = 255;
            result_color.g = 255;
            result_color.b = 255;
            result_color.a = 255;
        break;

        //Color not found = fatal_error
        default:
            fatal_error("Couldn't find required color !");
        break;
    }

    //Return result
    return result_color;
}
