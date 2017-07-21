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

    //Return newly created character
    return new_character;
}




