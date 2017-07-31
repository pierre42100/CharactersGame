/**
 * UI functions - Source file
 *
 * This file handle the main graphical operations
 *
 * @author Pierre HUBERT
 */

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "logging.h"
#include "../config.h"
#include "ui.h"

/**
 * Variables definition
 */
static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;
static SDL_Texture *textures[NUMBER_TEXTURES];
static TTF_Font *main_font = NULL;


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
 * Display UI loading message
 */
void ui_display_loading_message(){

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


/**
 * Fonts functions
 */

/**
 * Initializate font library & open main programm font
 *
 * @param const char *filename Path to the TTF file
 * @param int ptsize Characters size to use
 */
void ui_font_init(const char *filename, int ptsize){

    //Try to initializate TTF library
    if(TTF_Init() != 0)
        fatal_error("Couldn't initializate TTF library !");

    //Try to load ttf file
    main_font = TTF_OpenFont(filename, ptsize);

    //Check for errors
    if(main_font == NULL)
        fatal_error("Couldn't load font library !");

    //End of function
    return;
}

/**
 * Quit font library
 */
void ui_font_quit(){

    //Check if the main font was loaded
    if(main_font != NULL)
        TTF_CloseFont(main_font);

    //Quit TTF (if initializated)
    if(TTF_WasInit() == 1)
        TTF_Quit();

}

/**
 * Write a text on a texture at a specified position
 *
 * @param SDL_Texture *target_texture Target texture (NULL to specify renderer)
 * @param const char *message The message to write on the renderer
 * @param SDL_Color *color The color of the text to write
 * @param int x
 * @param int y > Coordinates of the text
 * @param int required_text_height The height of the text
 * @param int style The style of the text
 * @param int render_mode The mode to use to render text
 */
void ui_font_write_texture(SDL_Texture *target_texture, const char *message, SDL_Color color, int x, int y, int required_text_height, int style, int render_mode){

    //Declare variables
    SDL_Surface *text_surface = NULL;
    SDL_Texture *text_texture = NULL;
    int text_width = 0;
    int text_height = 0;

    //Log action
    log_message(LOG_VERBOSE, "Writing a message on a texture");

    //Prepare rendering
    ui_font_prepare_rendering(style);

    //Create a surface containing the text accordingly to the rendering mode
    switch (render_mode){

        //Solid rendering : fatest, but poorest quality
        case FONT_RENDERING_SOLID:
            text_surface = TTF_RenderText_Solid(main_font, message, color);
        break;

        //Shaded rendering : intermediate, better quality, but no transparency support
        case FONT_RENDERING_SHADED:
            text_surface = TTF_RenderText_Shaded(main_font, message, color, ui_get_color(UI_COLOR_WHITE));
        break;

        //Blended rendering : slowlest, but with transparency support + better quality
        case FONT_RENDERING_BLENDED:
            text_surface = TTF_RenderText_Blended(main_font, message, color);
        break;

        default:
            fatal_error("TTF : Unrecognized rendering mode !");
        break;
    }

    //Check for errors
    if(text_surface == NULL)
        fatal_error("Couldn't render message !");

    //Convert the surface into a texture
    text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);

    //Check for errors
    if(text_texture == NULL)
        fatal_error("TTF function : Couldn't convert a surface containing a text message into a texture !");

    //Determine texture target area
    if(SDL_QueryTexture(text_texture, NULL, NULL, &text_width, &text_height) != 0)
        fatal_error("TTF function : Couldn't query newly created texture !");
    SDL_Rect target_area = {x, y, text_width*((float)required_text_height/text_height), required_text_height};

    //Set the texture as the rendering target
    SDL_SetRenderTarget(renderer, target_texture);

    //Copy the text
    SDL_RenderCopy(renderer, text_texture, NULL, &target_area);

    //Make the renderer as the new target
    SDL_SetRenderTarget(renderer, NULL);

    //Free memory
    SDL_FreeSurface(text_surface);
    SDL_DestroyTexture(text_texture);
}

/**
 * Prepare text rendering
 *
 * @param int style The style of the text
 */
void ui_font_prepare_rendering(int style){
    //Declare variables
    int ttf_style = -1;

    //Determine style
    switch (style){
        case FONT_STYLE_NORMAL:
            ttf_style = TTF_STYLE_NORMAL;
        break;

        case FONT_STYLE_ITALIC:
            ttf_style = TTF_STYLE_ITALIC;
        break;

        case FONT_STYLE_STRIKETHROUGH:
            ttf_style = TTF_STYLE_STRIKETHROUGH;
        break;

        case FONT_STYLE_UNDERLINE:
            ttf_style = TTF_STYLE_UNDERLINE;
        break;

        case FONT_STYLE_BOLD:
            ttf_style = TTF_STYLE_BOLD;
        break;

        default:
            fatal_error("TTF : Unrecognized style !");
        break;
    }

    //Set style
    TTF_SetFontStyle(main_font, ttf_style);
}


/**
 * Determine the room taken by a text before rendering it
 *
 * @param const char *message The message to calculate
 * @param int style The style of the text
 * @param int *width The width of the text (target pointer)
 * @param int required_height The height of the text
 */
void ui_font_determine_text_size(const char *message, int style, int *width, int required_height){

    //Declare variable
    int rendered_height = 0;

    //Define TTF options
    ui_font_prepare_rendering(style);

    //Get the potential size of the text
    TTF_SizeText(main_font, message, width, &rendered_height);

    //Compute new text width
    *width = (int) (*width)*((float)required_height/rendered_height);

}
