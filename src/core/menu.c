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
 * @param const char[] options Options of the menu
 * @param int texture_number The number of the texture in main texture array
 */
Menu menu_create(const char *options[], int texture_number){

    //Create menu object
    Menu menu;

    //Initialize options
    menu.curr_option = 0;
    menu.number_options = 0;

    for(int i = 0; i < MENU_MAXIMUM_OPTIONS; i++){

        //Check if current entry could be useful
        if(strlen(&options[i]) < 2)
            break; //End of initialization

        //Copy entry in options array
        menu.options[i] = NULL;
        menu.options[i] = malloc(sizeof(char)*strlen(&options[i]));

        //Check for allocation erro
        if(menu.options[i] == NULL)
            fatal_error("Couldn't allocate memory !");

        //Copy menu option in array
        strcpy(menu.options[i], &options[i]);

        //Increment options number counter
        menu.number_options++;

    }

    //Initialize the texture of the menu
    menu.texture_number = texture_number;
    menu_init_texture(&menu);

    //Return result
    return menu;

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
    UI_Text text = ui_font_create_variable("hello", 32);
    ui_font_set_style(&text, FONT_STYLE_ITALIC);

    //Fill the menu with the options
    for(int i = 0; i < menu->number_options; i++){

        //Update coordinates
        ui_font_set_coordinates(&text, 0, i*32);

        //Update message
        ui_font_set_message(&text, menu->options[i]);
        printf("MENU : : : : : : Number options : %d\n", menu->number_options);

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

    //Update renderer target
    SDL_SetRenderTarget(renderer, NULL);

    //Copy texture
    if(SDL_RenderCopy(renderer, ui_get_pointer_on_texture(menu->texture_number), NULL, NULL) != 0)
        log_message(LOG_ERROR, "Couldn't copy menu texture on renderer !");

    //Refresh window
    ui_refresh_window();

}
