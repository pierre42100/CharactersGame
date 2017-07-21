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
Character character_load(const char *filename, int target_texture);

/**
 * Moves a character
 *
 * @param Character *character The character to move
 * @param int movement The movement to perform
 */
void character_move(Character *character, int movement);

/**
 * Destroy a character
 *
 * @param Character *character The character to destroy
 */
void character_destroy(Character *character);

#endif // CHARACTER_H_INCLUDED
