/**
 * Menu system - Source file
 *
 * @author Pierre Hubert
 */

#include <SDL2/SDL.h>

#include "../config.h"
#include "logging.h"
#include "menu.h"
#include "game.h"
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

    //Add star
    if(ui_is_texture_loaded(TEXTURE_STAR) != 1)
        ui_load_image_into_texture(RES_DIRECTORY"star.png", TEXTURE_STAR);

    //Get informations about the star
    int star_w, star_h;
    SDL_QueryTexture(ui_get_pointer_on_texture(TEXTURE_STAR), NULL, NULL, &star_w, &star_h);

    //Copy the start on the renderer
    SDL_Rect star_target_area = {MENU_MIN_POS_X-star_w-5, MENU_MIN_POS_Y + menu->curr_option*32, star_w, star_h};
    SDL_RenderCopy(renderer, ui_get_pointer_on_texture(TEXTURE_STAR), NULL, &star_target_area);


    //Refresh window
    ui_refresh_window();

}

/**
 * Handles events for a menu
 *
 * @param Menu *menu Target menu
 * @param SDL_Event *event Event to handle
 * @return int value Selected value by user (0 for none)
 */
int menu_handle_event(Menu *menu, SDL_Event *event){

    switch(event->type){
        case SDL_KEYDOWN:
            //The game screen will have to be updated
            game_screen_to_update(1);

            switch(event->key.keysym.sym){

                case SDLK_DOWN:
                    //Change selected menu option
                    menu_change_selected_option(menu, menu->curr_option+1);
                break;

                case SDLK_UP:
                    //Change selected menu option
                    menu_change_selected_option(menu, menu->curr_option-1);
                break;

                case SDLK_RETURN:
                case SDLK_RETURN2:
                case SDLK_KP_ENTER:
                    //Return selected option
                    return menu->options[menu->curr_option]->value;
                break;

            }

            break;
    }

    //It seems that nothing important happened
    return 0;
}


/**
 * Change selected menu option
 *
 * @param Menu *menu The menu to update
 * @param int new_option The new option number
 */
void menu_change_selected_option(Menu *menu, int new_option){

    //Check if the new option exists or not
    if(new_option < 0 || menu->number_options <= new_option)
        return;

    //Save new option
    menu->curr_option = new_option;
}
