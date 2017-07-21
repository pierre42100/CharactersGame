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

    //Character speed
    int speed;

};
typedef struct Character Character;

/**
 * Define character movements
 */
#define MOVE_CHARACTER_LEFT 1
#define MOVE_CHARACTER_RIGHT 2
#define MOVE_CHARACTER_UP 3
#define MOVE_CHARACTER_DOWN 4


/**
 * Loads a character
 *
 * @param const char *filename The name of the image representing the character
 * @param int target_texture The ID of the target texture for the character
 * @return Character The created character
 */
Character load_character(const char *filename, int target_texture);

/**
 * Moves a characer
 *
 * @param Character *character The character to move
 * @param int movement The movement to perform
 */
void move_character(Character *character, int movement);

#endif // CHARACTER_H_INCLUDED
