#ifndef MAIN_CHARACTER_H_INCLUDED
#define MAIN_CHARACTER_H_INCLUDED

/**
 * Main character header file
 *
 * @author Pierre HUBERT
 */

#include "../core/character.h"

/**
 * Define main character object
 */
typedef struct MainCharacter {

    //Generic informations about the character
    Character character;

    //Score of the main character
    int score;


} MainCharacter;

/**
 * Create the main character
 */
void main_character_create();

/**
 * Destroy the main character
 */
void main_character_destroy();

/**
 * Display the main character
 */
void main_character_display();

/**
 * Set new location for the main character
 *
 * @param int x
 * @param int y > Coordinates of the new location
 */
void main_character_set_location(int x, int y);

/**
 * Set new abscisse for the main character
 *
 * @param int x
 */
void main_character_set_pos_x(int x);

/**
 * Set new ordonee for the main character
 *
 * @param int y
 */
void main_character_set_pos_y(int y);

/**
 * Move the main character
 *
 * @param int movement The movement to perform
 */
void main_character_move(int movement);

/**
 * Get the number of lives of the main character
 *
 * @return int The number of lives of the main character
 */
int main_character_get_lives();

/**
 * Make the main character lose one live
 */
void main_character_lose_one_live();

/**
 * Get the score of the main character
 */
int main_character_get_score();

/**
 * Get the age of the main character
 *
 * @return int age The age of the main character
 */
int main_character_get_age();

#endif // MAIN_CHARACTER_H_INCLUDED
