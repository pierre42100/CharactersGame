#ifndef GAME_STARTED_H_INCLUDED
#define GAME_STARTED_H_INCLUDED

/**
 * Game started header file
 *
 * @author Pierre HUBERT
 */

#include <SDL2/SDL.h>

/**
 * Start the game
 */
void game_started_start();

/**
 * Handle game started events
 *
 * @param SDL_Event *event The event to process
 */
void game_started_handle_events(SDL_Event *event);

/**
 * Update game started window
 */
void game_started_refresh_window();

/**
 * Stop the current game
 */
void game_started_stop();

#endif // GAME_STARTED_H_INCLUDED
