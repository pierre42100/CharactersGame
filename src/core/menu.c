/**
 * Menu system - Source file
 *
 * @author Pierre Hubert
 */

#include <SDL2/SDL.h>

#include "../config.h"
#include "logging.h"
#include "menu.h"
#include "ui.h"
#include "ui_fonts.h"

extern SDL_Renderer *renderer;

/**
 * Create a new menu
 *
 * @param int texture_number The number of the texture in main texture array
 */
Menu menu_create(int texture_number){

    //Create menu object
    Menu menu;

    //Initialize options
    menu.curr_option = 0;
    menu.number_options = 0;

    //Initialize the texture of the menu
    menu.texture_number = texture_number;

    //Return result
    return menu;

}

/**
 * Add a new menu option
 *
 * @param Menu *menu The target menu
 * @param const char *name Option name
 * @param int value Value of the option
 */
void menu_add_option(Menu *menu, const char *name, int value){

    //First, destroy previous version of the texture (if any)
    if(ui_is_texture_loaded(menu->texture_number) == 1)
        ui_destroy_texture(menu->texture_number);

    //Create menu entry
    Menu_Entry entry;

    //Copy option name
    entry.name = malloc(sizeof(char)*strlen(name));
    if(entry.name == NULL)
        fatal_error("Couldn't allocate memory for an entry name of a menu !");
    strcpy(entry.name, name);

    //Copy option value
    entry.value = value;

    //Add entry to the entry list
    menu->options[menu->number_options] = malloc(sizeof(Menu));
    if(menu->options[menu->number_options] == NULL)
        fatal_error("Couldn't allocate memory for an entry of a menu !");
    *menu->options[menu->number_options] = entry;

    //Increment the number option
    menu->number_options++;

}

/**
 * Initialize the texture of the menu
 *
 * @param Menu *menu The menu with the texture to initializate
 */
void menu_init_texture(Menu *menu){

    //First, destroy previous version of the texture (if any)
    if(ui_is_texture_loaded(menu->texture_number) == 1)
        ui_destroy_texture(menu->texture_number);

    //Create the texture
    ui_create_texture(menu->texture_number, WINDOW_WIDTH, WINDOW_HEIGHT, 1);

    //Prepare text rendering
    UI_Text text = ui_font_create_variable("no value", 32);
    ui_font_set_style(&text, FONT_STYLE_ITALIC);
    ui_font_set_target_texture(&text, ui_get_pointer_on_texture(menu->texture_number));

    //Fill the menu with the options
    for(int i = 0; i < menu->number_options; i++){

        //Update coordinates
        ui_font_set_coordinates(&text, MENU_MIN_POS_X, MENU_MIN_POS_Y+i*32);

        //Update message
        ui_font_set_message(&text, menu->options[i]->name);

        //Write message
        ui_font_write_texture(&text);

    }
}

/**
 * Display a menu
 *
 * @param Menu *menu The menu to display
 */
void menu_display(Menu *menu){
    //Log action
    log_message(LOG_VERBOSE, "Display a menu");

    //Check if it is required to initializate texture
    if(ui_is_texture_loaded(menu->texture_number) != 1)
        menu_init_texture(menu);

    //Load background
    ui_display_background();

    //Update renderer target
    SDL_SetRenderTarget(renderer, NULL);

    //Copy texture
    if(SDL_RenderCopy(renderer, ui_get_pointer_on_texture(menu->texture_number), NULL, NULL) != 0)
        log_message(LOG_ERROR, "Couldn't copy menu texture on renderer !");

    //Refresh window
    ui_refresh_window();

}
