/**
 * Heart character - Source file
 *
 * This character makes the user earn one
 * life when he gos over it.
 *
 * @author Pierre HUBERT
 */
#include <time.h>

#include "../config.h"
#include "../core/logging.h"
#include "../core/game.h"
#include "../core/ui.h"
#include "../core/ui_utils.h"
#include "../core/character.h"

#include "main_character.h"
#include "heart.h"

/**
 * Variables definition
 */
//Address of the last heart character
static Heart *last_heart = NULL;

/**
 * Create a heart character
 *
 * @param int x
 * @param int y > Coordinates of the first point of the heart character element
 * @param int regeneration_interval The minimum interval before the heart can be redeemed again
 * @return void
 */
void heart_create(int x, int y,  int regeneration_interval){

    //Declare variables
    Heart *new_heart = NULL;

    //Allocate memory for the heart character
    new_heart = malloc(sizeof(Heart));

    //Check for errors
    if(new_heart == NULL)
        fatal_error("Couldn't allocate memory for the new heart !");

    //Load the character
    new_heart->character = character_load(PATH_IMG_HEART, TEXTURE_HEART_CHARACTER);

    //Check if it isn't the first heart of the list
    if(new_heart != NULL){
        //Add the new heart character address to the last heart character item of the list
        new_heart->nextHeart = last_heart;
    }
    else {
        new_heart->nextHeart = NULL;
    }

    //Replace the last item of the list with the new heart character
    last_heart = new_heart;

    //Update heart character coordinates
    new_heart->character.pos_x = x;
    new_heart->character.pos_y = y;

    //Update heart appeareance frequrency
    new_heart->regeneration_interval = regeneration_interval;

    //Reset counter
    new_heart->last_use = 0;
}

/**
 * Destroy all the heart characters
 *
 * @return void
 */
void heart_destroy_all(){

    //Declare variables
    Heart *curr_heart = NULL;

    //Check if there isn't any heart character to destroy
    if(last_heart == NULL)
        return; //Nothing to be done

    //Else process each heart character to delete them
    curr_heart = last_heart;
    while(last_heart != NULL){

        //Save the next heart character reference
        last_heart = curr_heart->nextHeart;

        //Delete the current heart character (free memory)
        free(curr_heart);

        curr_heart = last_heart;

    }

}


/**
 * Display the hearts
 *
 * @return void
 */
void heart_display_all(){

    //Declare variables
    Heart *curr_heart = NULL;

    //Check if there is at least one heart character
    if(last_heart == NULL)
        return; //Nothing to be done


    //Process all the hearts
    curr_heart = last_heart;
    while(curr_heart != NULL){

        //Display the heart character (only if available)
        if((time(NULL) - curr_heart->last_use) > curr_heart->regeneration_interval)
            character_display(&curr_heart->character);

        //Get the next heart character memory address
        curr_heart = curr_heart->nextHeart;

    }
}

/**
 * Check if a character is on a heart character or not
 *
 * @param Character *character The character to check
 * @return int 1 = Yes, the character is on a heart character / 0 = No, the character isn't on a heart character
 */
int heart_check_character_presence(Character *character){

    //Declare variables
    Heart *curr_heart = NULL;

    //Check if at least one character exists before
    if(last_heart == NULL)
        return 0; //There isn't any heart character

    //Process all the hearts
    curr_heart = last_heart;
    while(curr_heart != NULL){

        //Check heart character
        if(character_check_collision(character, &curr_heart->character) != 0)
            return 1; //There is a collision

        //Get the next heart character memory address
        curr_heart = curr_heart->nextHeart;

    }

    //If we get there, there isn't any collision
    return 0;

}

/**
 * Check if the main character is on a heart or not
 *
 * @param Character *character The character object of the main character
 */
void heart_check_main_character(Character *character){

    //Retrieve game state
    if(game_get_state() != GAME_STATE_STARTED)
        return; //Not any game started

    //Log action
    log_message(LOG_VERBOSE, "Check if main character is on a heart or not...");

    //Declare variables
    Heart *curr_heart = NULL;

    //Check if at least one character exists before
    if(last_heart == NULL)
        return; //There isn't any heart character


    //Process all the hearts
    curr_heart = last_heart;
    while(curr_heart != NULL){

        //Check heart character
        if(character_check_collision(character, &curr_heart->character) != 0){

            //Check if the heart can be eaten or not
            if((time(NULL) - curr_heart->last_use) > curr_heart->regeneration_interval){

                //Increase main character score
                main_character_earn_live();

                //Update counter
                curr_heart->last_use = time(NULL);
            }

            return; //There is a collision
        }

        //Get the next heart character memory address
        curr_heart = curr_heart->nextHeart;

    }
}
