/**
 * UI functions - Header file
 *
 * This file handles the main graphical operations
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
#define NUMBER_TEXTURES 16

//Included images
#define TEXTURE_GRASS 0
#define TEXTURE_MAIN_CHARACTER 3
#define TEXTURE_WALL 6
#define TEXTURE_STAR 8
#define TEXTURE_HEART 10
#define TEXTURE_CROSS 11
#define TEXTURE_PIZZA 12
#define TEXTURE_HEART_CHARACTER 13
#define TEXTURE_MONSTER_CHARACTER 14
#define TEXTURE_CURSOR 15

//Generated textures
#define TEXTURE_BACKGROUND 1
#define TEXTURE_LOADING_MSG 2
#define TEXTURE_MAIN_MENU 4
#define TEXTURE_PAUSED_MENU 5
#define TEXTURE_GAME_OVER 7
#define TEXTURE_LIFES_MESSAGE 9


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
 * Destroy a specified texture
 *
 * @param int texture_number The texture to destroy
 */
void ui_destroy_texture(int texture_number);

/**
 * Load game background into a texture
 */
void ui_load_background();

/**
 * Display the background on the screen (clean it)
 */
void ui_display_background();

/**
 * Color functions
 */

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


#endif // UI_H_INCLUDED
