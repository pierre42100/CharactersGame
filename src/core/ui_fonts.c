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
