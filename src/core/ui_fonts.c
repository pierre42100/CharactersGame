/**
 * UI fonts - Functions file
 *
 * @author Pierre HUBERT
 */

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "logging.h"
#include "ui.h"
#include "ui_fonts.h"

/**
 * Variables definition
 */
extern SDL_Renderer *renderer;
static TTF_Font *main_font = NULL;

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
 * Create a text variable
 *
 * @param const char *message The message of the object
 * @param int height The height of the newly created message
 * @return UI_Text Created write object with default options
 */
UI_Text ui_font_create_variable(char *message, int height){
    //Declare variables
    UI_Text data;

    //Set message content & height
    data.message = message;
    data.text_height = height;

    //Setting default values
    data.style = FONT_STYLE_NORMAL;
    data.render_mode = FONT_RENDERING_SOLID;
    data.color = ui_get_color(UI_COLOR_WHITE);

    //Compute message size
    ui_font_determine_text_size(&data);

    //Return result
    return data;
}

/**
 * Write a text object on a texture
 *
 * @param UI_Text *data Informations about the text object
 */
void ui_font_write_texture(UI_Text *data){

    //Declare variables
    SDL_Surface *text_surface = NULL;
    SDL_Texture *temp_text_texture = NULL;
    int temp_texture_width = 0;
    int temp_texture_height = 0;

    //Log action
    log_message(LOG_VERBOSE, "Writing a message on a texture");

    //Prepare rendering
    ui_font_prepare_rendering(data->style);

    //Create a surface containing the text accordingly to the rendering mode
    switch (data->render_mode){

        //Solid rendering : fatest, but poorest quality
        case FONT_RENDERING_SOLID:
            text_surface = TTF_RenderText_Solid(main_font, data->message, data->color);
        break;

        //Shaded rendering : intermediate, better quality, but no transparency support
        case FONT_RENDERING_SHADED:
            text_surface = TTF_RenderText_Shaded(main_font, data->message, data->color, data->bgcolor);
        break;

        //Blended rendering : slowlest, but with transparency support + better quality
        case FONT_RENDERING_BLENDED:
            text_surface = TTF_RenderText_Blended(main_font, data->message, data->color);
        break;

        default:
            fatal_error("TTF : Unrecognized rendering mode !");
        break;
    }

    //Check for errors
    if(text_surface == NULL)
        fatal_error("Couldn't render message !");

    //Convert the surface into a texture
    temp_text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);

    //Check for errors
    if(temp_text_texture == NULL)
        fatal_error("TTF function : Couldn't convert a surface containing a text message into a texture !");

    //Determine texture target area
    if(SDL_QueryTexture(temp_text_texture, NULL, NULL, &temp_texture_width, &temp_texture_height) != 0)
        fatal_error("TTF function : Couldn't query newly created texture !");
    SDL_Rect target_area = {data->x, data->y, data->text_width, data->text_height};

    //Set the texture as the rendering target
    SDL_SetRenderTarget(renderer, data->targetTexture);

    //Copy the text
    SDL_RenderCopy(renderer, temp_text_texture, NULL, &target_area);

    //Make the renderer as the new target
    SDL_SetRenderTarget(renderer, NULL);

    //Free memory
    SDL_FreeSurface(text_surface);
    SDL_DestroyTexture(temp_text_texture);
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
 * @param UI_Text *data Informations about the text object
 */
void ui_font_determine_text_size(UI_Text *data){

    //Declare variable
    int rendered_height = 0;
    int rendered_width = 0;

    //Define TTF options
    ui_font_prepare_rendering(data->style);

    //Get the potential size of the text
    TTF_SizeText(main_font, data->message, &rendered_width, &rendered_height);

    //Compute new text width
    data->text_width = (int) rendered_width*((float)data->text_height/rendered_height);

}


/**
 * Update the font style of a message structure
 *
 * @param UI_Text *data Informations about the text object to update
 * @param int new_style The new style to use
 */
void ui_font_set_style(UI_Text *data, int new_style){

    //Set the new style
    data->style = new_style;

    //Compute again text size
    ui_font_determine_text_size(data);

}

/**
 * Set the target texture of a message structure
 *
 * @param UI_Text *data Informations about the text object to update
 * @param SDL_Texture *texture The target texture of the message (NULL = Renderer)
 */
void ui_font_set_target_texture(UI_Text *data, SDL_Texture *texture){

    //Set the new target texture
    data->targetTexture = texture;

}

/**
 * Set the coordinates where a message structure should be applied
 *
 * @param UI_Text *data Informations about the text object to update
 * @param int x
 * @param int y > Coordinates of the texture
 */
void ui_font_set_coordinates(UI_Text *data, int x, int y){

    //Update coordinates
    data->x = x;
    data->y = y;

}

/**
 * Set a new message to a text structure
 *
 * @param UI_Text *data Informations about the text object to update
 * @param char *message The new message
 */
void ui_font_set_message(UI_Text *data, char *message){

    //Set new message
    data->message = message;

    //Recompute text width
    ui_font_determine_text_size(data);

}

/**
 * Set new message rendering mode
 *
 * @param UI_Text *data Informations about the text object to update
 * @param int renderer The rendering option
 */
void ui_font_set_rendering_mode(UI_Text *data, int rendering_mode){

    data->render_mode = rendering_mode;

}
