#ifndef HEART_H_INCLUDED
#define HEART_H_INCLUDED

/**
 * Heart character - Header file
 *
 * @author Pierre HUBERT
 */

/**
 * Defines heart object
 */
typedef struct Heart {

    //Root character
    Character character;

    //Position of the next character
    struct Heart *nextHeart;

    //Intervals of the heart (in seconds)
    unsigned long last_use;
    int regeneration_interval;

} Heart;


/**
 * Create a heart character
 *
 * @param int x
 * @param int y > Coordinates of the first point of the wall element
 * @param int regeneration_interval The minimum interval before the heart can be eaten again
 * @return void
 */
void heart_create(int x, int y, int regeneration_interval);

/**
 * Destroy all the heart characters
 *
 * @return void
 */
void heart_destroy_all();

/**
 * Display the heart characters
 *
 * @return void
 */
void heart_display_all();

/**
 * Check if a character is on a heart character or not
 *
 * @param Character *character The character to check
 * @return int 1 = Yes, the character is on the character / 0 = No, the character isn't on a heart character
 */
int heart_check_character_presence(Character *character);

/**
 * Check if the main character is on a heart or not
 *
 * @param Character *character The character object of the main character
 */
void heart_check_main_character(Character *character);

#endif // HEART_H_INCLUDED
