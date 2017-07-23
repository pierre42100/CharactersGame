#ifndef WALL_H_INCLUDED
#define WALL_H_INCLUDED

/**
 * Wall objects - Header file
 *
 * @author Pierre HUBERT
 */

#include "../character.h"

/**
 * Defines wall object
 */
typedef struct Wall {

    //Root character
    Character character;

    //Position of the next character
    struct Wall *nextWall;

} Wall;


/**
 * Create a wall
 *
 * @param int x
 * @param int y > Coordinates of the first point of the wall element
 * @return void
 */
void wall_create(int x, int y);

/**
 * Destroy all the walls
 *
 * @return void
 */
void wall_destroy_all();

/**
 * Display the walls
 *
 * @return void
 */
void wall_display_all();

#endif // WALL_H_INCLUDED
