/**
 * UI functions - Header file
 *
 * This file handle the main graphical operations
 *
 * @author Pierre HUBERT
 */
#ifndef UI_H_INCLUDED
#define UI_H_INCLUDED

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "character.h"

/**
 * Textures definition
 */
#define NUMBER_TEXTURES 8
#define TEXTURE_GRASS 0
#define TEXTURE_BACKGROUND 1
#define TEXTURE_LOADING_MSG 2
#define TEXTURE_MAIN_CHARACTER 3
#define TEXTURE_MENU 4
#define TEXTURE_PAUSED_MENU 5
#define TEXTURE_WALL 6
#define TEXTURE_GAME_OVER 7

/**
 * Initializate the SDL library plus create programm windows & renderer
 */
void ui_init();

/**
 * Terminate and close UI
 */
void ui_quit();

/**
 * Refresh the window
 */
void ui_refresh_window();

/**
 * Set the window icon
 *
 * @param const char *filename The name of the image to use as an icon
 */
void ui_set_window_icon(const char *filename);

/**
 * Get the pointer on the renderer
 *
 * @return SDL_Renderer *renderer Pointer on renderer
 */
SDL_Renderer* ui_get_renderer();

/**
 * Get the pointer on a texture entry
 *
 * @param int texture_number The number of the texture to get
 * @return SDL_Texture* Pointer on the desired texture
 */
SDL_Texture* ui_get_pointer_on_texture(int texture_number);

/**
 * Load an image and save it in a texture
 *
 * @param const char *filename The name of the image to load
 * @param int target_texture The target texture of the image
 * @return void (Fatal error in case of failure)
 */
void ui_load_image_into_texture(const char *filename, int target_texture);

/**
 * Create a texture in the array of textures and return it as result
 *
 * @param int target_texture The target texture
 * @param int w
 * @param int h > Coordinates of the texture
 * @param int force Force the texture to be created (destroy any previous texture)
 */
SDL_Texture* ui_create_texture(int target_texture, int w, int h, int force);

/**
 * Check if a texture was loaded or not
 *
 * @param int texture_number The number of the texture to check
 * @return int 1 = yes / 0 = no
 */
int ui_is_texture_loaded(int texture_number);

/**
 * Load game background into a texture
 */
void ui_load_background();

/**
 * Display the background on the screen (clean it)
 */
void ui_display_background();

/**
 * Display UI loading message
 */
void ui_display_loading_message();

/**
 * Display a character
 *
 * @param Character character The character to display
 * @return void (Fatal error in case of failure)
 */
void character_display(Character *character);

/**
 * Colors definition
 */
#define UI_COLOR_WHITE 0

/**
 * Get a specific color
 *
 * @param int color The color to get
 * @return SDL_Color The required color
 */
SDL_Color ui_get_color(int color);

/**
 * Font styles definition
 */
#define FONT_STYLE_NORMAL 0
#define FONT_STYLE_BOLD 1
#define FONT_STYLE_ITALIC 2
#define FONT_STYLE_UNDERLINE 3
#define FONT_STYLE_STRIKETHROUGH 4

/**
 * Font rendering modes
 */
#define FONT_RENDERING_SOLID 0
#define FONT_RENDERING_SHADED 1
#define FONT_RENDERING_BLENDED 2


/**
 * Initializate font library & open main programm font
 *
 * @param const char *filename Path to the TTF file
 * @param int ptsize Characters size to use
 */
void ui_font_init(const char *filename, int ptsize);

/**
 * Quit font library
 */
void ui_font_quit();

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
void ui_font_write_texture(SDL_Texture *target_texture, const char *message, SDL_Color color, int x, int y, int required_text_height, int style, int render_mode);

/**
 * Prepare text rendering
 *
 * @param int style The style of the text
 */
void ui_font_prepare_rendering(int style);

/**
 * Determine the room taken by a text before rendering it
 *
 * @param const char *message The message to calculate
 * @param int style The style of the text
 * @param int *width The width of the text (target pointer)
 * @param int required_height The height of the text
 */
void ui_font_determine_text_size(const char *message, int style, int *width, int required_height);

#endif // UI_H_INCLUDED
