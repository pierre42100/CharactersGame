/**
 * Main character functions file
 *
 * @author Pierre HUBERT
 */

#include "config.h"
#include "ui.h"
#include "logging.h"
#include "character.h"
#include "main_character.h"

static Character *main_character = NULL;

/**
 * Create the main character
 */
void main_character_create(){

    //Verbose message
    log_message(LOG_VERBOSE, "Creating main character...");

    //Allocate memory for the character
    main_character = malloc(sizeof(Character));

    if(main_character == NULL)
        fatal_error("Couldn't allocate memory for the main character!");

    //Create the character
    *main_character = load_character(RES_DIRECTORY"character.png", TEXTURE_MAIN_CHARACTER);

    //Place the character on the center of the screen
    main_character->pos_x = (WINDOW_WIDTH-main_character->w)/2;
    main_character->pos_y = (WINDOW_HEIGHT-main_character->h)/2;

    //End of function
    return;

}

/**
 * Display the main character
 */
void main_character_display(){
    //Display the main character
    character_display(main_character);
}
