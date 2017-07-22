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
 * Stop the current game
 */
void game_started_stop();

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
 * Parse game JSON file
 *
 * @param const char *filename The name of the file to parse
 */
void parse_game_json_file(const char *filename);

#endif // GAME_STARTED_H_INCLUDED
