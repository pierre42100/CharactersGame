/**
 * Cross character - Source file
 *
 * @author Pierre HUBERT
 */

#include "../config.h"
#include "../core/logging.h"
#include "../core/ui.h"
#include "../core/ui_utils.h"
#include "../core/character.h"

#include "cross.h"

/**
 * Variables definition
 */
//Address of the last cross character
static Cross *last_cross = NULL;

/**
 * Create a cross character
 *
 * @param int x
 * @param int y > Coordinates of the first point of the cross character element
 * @return void
 */
void cross_create(int x, int y){

    //Declare variables
    Cross *new_cross = NULL;

    //Allocate memory for the cross character
    new_cross = malloc(sizeof(Cross));

    //Check for errors
    if(new_cross == NULL)
        fatal_error("Couldn't allocate memory for the new cross !");

    //Load the character
    new_cross->character = character_load(PATH_IMG_CROSS, TEXTURE_CROSS);

    //Check if it isn't the first cross of the list
    if(new_cross != NULL){
        //Add the new cross character address to the last cross character item of the list
        new_cross->nextCross = last_cross;
    }
    else {
        new_cross->nextCross = NULL;
    }

    //Replace the last item of the list with the new cross character
    last_cross = new_cross;

    //Update cross character coordinates
    new_cross->character.pos_x = x;
    new_cross->character.pos_y = y;
}

/**
 * Destroy all the cross characters
 *
 * @return void
 */
void cross_destroy_all(){

    //Declare variables
    Cross *curr_cross = NULL;

    //Check if there isn't any wall to destroy
    if(last_cross == NULL)
        return; //Nothing to be done

    //Else process each cross character to delete them
    curr_cross = last_cross;
    while(last_cross != NULL){

        //Save the next cross character reference
        last_cross = curr_cross->nextCross;

        //Delete the current cross character (free memory)
        free(curr_cross);

        curr_cross = last_cross;

    }

}


/**
 * Display the crosses
 *
 * @return void
 */
void cross_display_all(){

    //Declare variables
    Cross *curr_cross = NULL;

    //Check if there is at least one cross character
    if(last_cross == NULL)
        return; //Nothing to be done


    //Process all the walls
    curr_cross = last_cross;
    while(curr_cross != NULL){

        //Display the cross character
        character_display(&curr_cross->character);

        //Get the next cross character memory address
        curr_cross = curr_cross->nextCross;

    }
}

/**
 * Check if a character is on a cross character or not
 *
 * @param Character *character The character to check
 * @return int 1 = Yes, the character is on a cross character / 0 = No, the character isn't on a cross character
 */
int cross_check_character_presence(Character *character){

    //Declare variables
    Cross *curr_cross = NULL;

    //Check if at least one character exists before
    if(last_cross == NULL)
        return 0; //There isn't any cross character

    //Process all the walls
    curr_cross = last_cross;
    while(curr_cross != NULL){

        //Check cross character
        if(character_check_collision(character, &curr_cross->character) != 0)
            return 1; //There is a collision

        //Get the next cross character memory address
        curr_cross = curr_cross->nextCross;

    }

    //If we get there, there isn't any collision
    return 0;

}
