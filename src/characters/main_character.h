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

#endif // MAIN_CHARACTER_H_INCLUDED
