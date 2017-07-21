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

#include "character.h"

/**
 * Variables definition
 */
#define NUMBER_TEXTURES 6
#define TEXTURE_GRASS 0
#define TEXTURE_BACKGROUND 1
#define TEXTURE_LOADING_MSG 2
#define TEXTURE_MAIN_CHARACTER 3
#define TEXTURE_MENU 4
#define TEXTURE_PAUSED_MENU 5

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

#endif // UI_H_INCLUDED
