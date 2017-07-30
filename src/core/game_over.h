#ifndef GAME_OVER_H_INCLUDED
#define GAME_OVER_H_INCLUDED

/**
 * Game over header file
 *
 * Handles actions when the user loses its game
 *
 * @author Pierre HUBERT
 */

#include <SDL2/SDL.h>

/**
 * Enter into game over mode
 */
void game_over_enter();

/**
 * Display the game over screen
 */
void game_over_display();

/**
 * Quit game over mode
 */
void game_over_quit();

/**
 * Handle game over state events
 *
 * @param SDL_Event *event The event to process
 */
void game_over_handles_events(SDL_Event *event);


#endif // GAME_OVER_H_INCLUDED
