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
Character character_load(const char *filename, int target_texture){

    //Create the character
    Character new_character;

    //Get the pointer on the texture
    new_character.texture = ui_get_pointer_on_texture(target_texture);

    //Load the character image (if it is not already available)
    if(new_character.texture == NULL){
        //Load image
        ui_load_image_into_texture(filename, target_texture);

        //Get the pointer on the new texture
        new_character.texture = ui_get_pointer_on_texture(target_texture);
    }

    //Check again texture availability
    if(new_character.texture == NULL){
        fatal_error("The texture image is not available after loading it to create the character !");
    }

    //Determine character coordinates
    SDL_QueryTexture(new_character.texture, NULL, NULL, &new_character.w, &new_character.h);

    //Reduce character size to fit to grid standard
    new_character.w = new_character.w / GAME_CELL_WIDTH;
    new_character.h = new_character.h / GAME_CELL_HEIGHT;

    //Define default character speed
    new_character.speed = 1;

    //Return newly created character
    return new_character;
}


/**
 * Moves a character
 *
 * @param Character *character The character to move
 * @param int movement The movement to perform
 */
void character_move(Character *character, int movement){

    //Log action (verbose)
    log_message(LOG_VERBOSE, "Move a character");

    //Save old character position
    character->old_pos_x = character->pos_x;
    character->old_pos_y = character->pos_y;

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

    //Check and correct if required the new coordinates of the character
    if(character->pos_x < 0)
        character->pos_x = 0;

    if(character->pos_x > GAME_NB_CELL_X_AXIS-1)
        character->pos_x = GAME_NB_CELL_X_AXIS-1;

    if(character->pos_y < 0)
        character->pos_y = 0;

    if(character->pos_y > GAME_NB_CELL_Y_AXIS-1)
        character->pos_y = GAME_NB_CELL_Y_AXIS-1;


    //End of function
    return;

}

/**
 * Destroy a character
 *
 * @param Character *character The character to destroy
 */
void character_destroy(Character *character){

    //Free memory
    free(character);

}

/**
 * Check for a collision between two characters
 *
 * @param Character *character_1 The first character
 * @param Character *character_2 The second character
 * @return int 1 = There is a collison / 0 = There isn't any collision
 */
int character_check_collision(Character *character_1, Character *character_2){

    //Create rectangles with coordinates of the two characters
    SDL_Rect rect1 = {character_1->pos_x, character_1->pos_y, character_1->w, character_1->h};
    SDL_Rect rect2 = {character_2->pos_x, character_2->pos_y, character_2->w, character_2->h};

    //Check if the two rectangles have common points or not
    return (SDL_HasIntersection(&rect1, &rect2) == SDL_TRUE) ? 1 : 0;
}
