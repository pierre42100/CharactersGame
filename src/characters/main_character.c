/**
 * Main character functions file
 *
 * @author Pierre HUBERT
 */

#include <stdio.h>
#include <stdlib.h>

#include "../config.h"
#include "../core/ui.h"
#include "../core/ui_utils.h"
#include "../core/logging.h"
#include "../core/character.h"
#include "main_character.h"

#include "wall.h"

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
    *main_character = character_load(RES_DIRECTORY"character.png", TEXTURE_MAIN_CHARACTER);

    //Place the character on the center of the screen
    main_character->pos_x = (GAME_NB_CELL_X_AXIS)/2;
    main_character->pos_y = (GAME_NB_CELL_Y_AXIS)/2;

    //Increase character speed
    main_character->speed = 1;

    //End of function
    return;

}

/**
 * Destroy the main character
 */
void main_character_destroy(){

    //Destroy the character
    character_destroy(main_character);

    //Reset cursor
    main_character = NULL;

}

/**
 * Display the main character
 */
void main_character_display(){
    //Display the main character
    character_display(main_character);
}

/**
 * Move the main character
 *
 * @param int movement The movement to perform
 */
void main_character_move(int movement){
    //Move the character
    character_move(main_character, movement);

    //Check if the new position of the character isn't on a wall
    if(wall_check_character_presence(main_character) == 1){
        //Put the character on its old positions
        main_character_set_location(main_character->old_pos_x, main_character->old_pos_y);

        //Log message
        log_message(LOG_VERBOSE, "New main character position denied: character can't walk on walls !");
    }

}

/**
 * Set new location for the main character
 *
 * @param int x
 * @param int y > Coordinates of the new location
 */
void main_character_set_location(int x, int y){
    main_character->pos_x = x;
    main_character->pos_y = y;
}

/**
 * Set new abscisse for the main character
 *
 * @param int x
 */
void main_character_set_pos_x(int x){
    main_character->pos_x = x;
}

/**
 * Set new ordonee for the main character
 *
 * @param int y
 */
void main_character_set_pos_y(int y){
    main_character->pos_y = y;
}
