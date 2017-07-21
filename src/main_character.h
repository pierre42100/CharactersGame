#ifndef MAIN_CHARACTER_H_INCLUDED
#define MAIN_CHARACTER_H_INCLUDED

/**
 * Main character header file
 *
 * @author Pierre HUBERT
 */


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
 * Move the main character
 *
 * @param int movement The movement to perform
 */
void main_character_move(int movement);

#endif // MAIN_CHARACTER_H_INCLUDED
