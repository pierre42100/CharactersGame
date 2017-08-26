#ifndef PIZZA_H_INCLUDED
#define PIZZA_H_INCLUDED

/**
 * Pizza object - Header file
 *
 * @author Pierre HUBERT
 */

/**
 * Defines pizza object
 */
typedef struct Pizza {

    //Root character
    Character character;

    //Position of the next character
    struct Pizza *nextPizza;

} Pizza;


/**
 * Create a pizza character
 *
 * @param int x
 * @param int y > Coordinates of the first point of the wall element
 * @return void
 */
void pizza_create(int x, int y);

/**
 * Destroy all the pizza characters
 *
 * @return void
 */
void pizza_destroy_all();

/**
 * Display the pizza characters
 *
 * @return void
 */
void pizza_display_all();

/**
 * Check if a character is on a pizza character or not
 *
 * @param Character *character The character to check
 * @return int 1 = Yes, the character is on the character / 0 = No, the character isn't on a pizza character
 */
int pizza_check_character_presence(Character *character);

#endif // PIZZA_H_INCLUDED
