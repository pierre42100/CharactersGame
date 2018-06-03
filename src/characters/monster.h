/**
 * Monster header file
 *
 * @author Pierre HUBERT
 */

#ifndef MONSTER_H_INCLUDED
#define MONSTER_H_INCLUDED

#include "../core/character.h"

/**
 * Defines monster structure
 */
typedef struct Monster {

    //Character object
    Character character;

    //Next monster
    struct Monster *next;

    //Speed of the monster (number of moves / seconds)
    int speed;

} Monster;


/**
 * Create a monster
 *
 * @param int x
 * @param int y
 * @param int speed
 */
void monster_create(int x, int y, int speed);

/**
 * Destroy all the monster characters
 */
void monster_destroy_all();

/**
 * Display all the characters
 */
void monster_display_all();

/**
 * Handles the actions to check whether the main
 * character is on a bug or not
 *
 * @param Character *character The character object of the main character
 */
void monster_check_main_character(Character *character);

/**
 * Move the monsters
 */
void monsters_move();

/**
 * Perform monsters routine
 */
void monster_routine();

#endif // MONSTER_H_INCLUDED
