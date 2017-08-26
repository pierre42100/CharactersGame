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

    //Intervals of the pizza (in seconds)
    unsigned long last_use;
    int regeneration_interval;

} Pizza;


/**
 * Create a pizza character
 *
 * @param int x
 * @param int y > Coordinates of the first point of the wall element
 * @param int regeneration_interval The minimum interval before the pizza can be eaten again
 * @return void
 */
void pizza_create(int x, int y, int regeneration_interval);

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

/**
 * Check if the main character is on a pizza or not
 *
 * @param Character *character The character object of the main character
 */
void pizza_check_main_character(Character *character);

#endif // PIZZA_H_INCLUDED
