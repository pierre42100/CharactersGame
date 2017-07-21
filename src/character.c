/**
 * Character functions file
 *
 * @author Pierre HUBERT
 */

#include <SDL2/SDL.h>

#include "config.h"
#include "logging.h"
#include "character.h"
#include "ui.h"

/**
 * Loads a character
 *
 * @param const char *filename The name of the image representing the character
 * @param int target_texture The ID of the target texture for the character
 * @return Character The created character
 */
Character load_character(const char *filename, int target_texture){

    //Create the character
    Character new_character;

    //Get the pointer on the texture
    new_character.texture = ui_get_pointer_on_texture(target_texture);

    //Load the character image (if it is not already available)
    if(new_character.texture == NULL){
        //Load image
        ui_load_image_into_texture(RES_DIRECTORY"character.png", target_texture);

        //Get the pointer on the new texture
        new_character.texture = ui_get_pointer_on_texture(target_texture);
    }

    //Check again texture availability
    if(new_character.texture == NULL){
        fatal_error("The texture image is not available after loading it to create the character !");
    }

    //Determine character coordinates
    SDL_QueryTexture(new_character.texture, NULL, NULL, &new_character.w, &new_character.h);

    //Define default character speed
    new_character.speed = 1;

    //Return newly created character
    return new_character;
}


/**
 * Moves a characer
 *
 * @param Character *character The character to move
 * @param int movement The movement to perform
 */
void move_character(Character *character, int movement){

    //Log action (verbose)
    log_message(LOG_VERBOSE, "Move a character");

    //Make the required movement
    switch(movement){

        //Move left
        case MOVE_CHARACTER_LEFT:
            character->pos_x -= character->speed;
        break;

        //Move right
        case MOVE_CHARACTER_RIGHT:
            character->pos_x += character->speed;
        break;

        //Move up
        case MOVE_CHARACTER_UP:
            character->pos_y -= character->speed;
        break;

        //Move down
        case MOVE_CHARACTER_DOWN:
            character->pos_y += character->speed;
        break;

    }

    //End of function
    return;

}