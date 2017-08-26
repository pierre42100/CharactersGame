#ifndef CROSS_H_INCLUDED
#define CROSS_H_INCLUDED

/**
 * Cross character - header file
 *
 * @author Pierre HUBERT
 */

#include "../core/character.h"

/**
 * Defines cross object
 */
typedef struct Cross {

    //Root character
    Character character;

    //Position of the next character
    struct Cross *nextCross;

} Cross;


/**
 * Create a cross character
 *
 * @param int x
 * @param int y > Coordinates of the first point of the wall element
 * @return void
 */
void cross_create(int x, int y);

/**
 * Destroy all the cross characters
 *
 * @return void
 */
void cross_destroy_all();

/**
 * Display the cross characters
 *
 * @return void
 */
void cross_display_all();

/**
 * Check if a character is on a cross character or not
 *
 * @param Character *character The character to check
 * @return int 1 = Yes, the character is on the character / 0 = No, the character isn't on a cross character
 */
int cross_check_character_presence(Character *character);

#endif // CROSS_H_INCLUDED
