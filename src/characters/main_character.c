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
#include "../core/game_over.h"
#include "main_character.h"

#include "wall.h"
#include "cross.h"

static MainCharacter *main_character = NULL;

/**
 * Create the main character
 */
void main_character_create(){

    //Verbose message
    log_message(LOG_VERBOSE, "Creating main character...");

    //Declare variables
    MainCharacter new_character;

    //Create the character
    new_character.character = character_load(RES_DIRECTORY"character.png", TEXTURE_MAIN_CHARACTER);

    //Place the character on the center of the screen
    new_character.character.pos_x = (GAME_NB_CELL_X_AXIS)/2;
    new_character.character.pos_y = (GAME_NB_CELL_Y_AXIS)/2;

    //Increase character speed
    new_character.character.speed = 1;

    //Set main character score to 0
    new_character.score = 0;

    //Save new main charater
    //Allocate memory for the character
    main_character = malloc(sizeof(MainCharacter));

    if(main_character == NULL)
        fatal_error("Couldn't allocate memory for the main character!");

    *main_character = new_character;

    //End of function
    return;

}

/**
 * Destroy the main character
 */
void main_character_destroy(){

    //Destroy the character
    //character_destroy(&main_character->character);
    free(main_character);

    //Reset cursor
    main_character = NULL;

}

/**
 * Display the main character
 */
void main_character_display(){
    //Display the main character
    character_display(&main_character->character);
}

/**
 * Move the main character
 *
 * @param int movement The movement to perform
 */
void main_character_move(int movement){
    //Move the character
    character_move(&main_character->character, movement);

    //Check if the new position of the character isn't on a wall
    if(wall_check_character_presence(&main_character->character) == 1){
        //Put the character on its old positions
        main_character_set_location(main_character->character.old_pos_x, main_character->character.old_pos_y);

        //Log message
        log_message(LOG_VERBOSE, "New main character position denied: character can't walk on walls !");
    }

    //Check if the position is on a cross character
    if(cross_check_character_presence(&main_character->character)){

        //Log event
        log_message(LOG_VERBOSE, "New main character has lost one live : is on a cross character !");

        //Character lose one live
        main_character_lose_one_live();

    }

}

/**
 * Set new location for the main character
 *
 * @param int x
 * @param int y > Coordinates of the new location
 */
void main_character_set_location(int x, int y){
    main_character->character.pos_x = x;
    main_character->character.pos_y = y;
}

/**
 * Set new abscisse for the main character
 *
 * @param int x
 */
void main_character_set_pos_x(int x){
    main_character->character.pos_x = x;
}

/**
 * Set new ordonee for the main character
 *
 * @param int y
 */
void main_character_set_pos_y(int y){
    main_character->character.pos_y = y;
}


/**
 * Get the number of lives of the main character
 *
 * @return int The number of lives of the main character
 */
int main_character_get_lives(){
    return main_character->character.lives;
}


/**
 * Make the main character lose one live
 */
void main_character_lose_one_live(){

    //Make the character lose one live
    if(main_character->character.lives > 0)
        main_character->character.lives--;

    //Check if character has 0 lives
    if(main_character->character.lives <= 0)
        //This is a game over
        game_over_enter();
}


/**
 * Get the score of the main character
 */
int main_character_get_score(){
    //Return the score of the main character
    return main_character->score;
}
