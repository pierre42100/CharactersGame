#ifndef CHARACTER_H_INCLUDED
#define CHARACTER_H_INCLUDED

/**
 * Character header file
 *
 * @author Pierre HUBERT
 */

#include <SDL2/SDL.h>

/**
 * Defines Character object
 */
struct Character {

    //Current position on the screen
    int pos_x;
    int pos_y;

    //Character image
    SDL_Texture *texture;

    //Character size
    int w;
    int h;

};
typedef struct Character Character;


/**
 * Loads a character
 *
 * @param const char *filename The name of the image representing the character
 * @param int target_texture The ID of the target texture for the character
 * @return Character The created character
 */
Character load_character(const char *filename, int target_texture);

#endif // CHARACTER_H_INCLUDED
