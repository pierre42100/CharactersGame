#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

/**
 * Game functions - Header file
 *
 * @author Pierre HUBERT
 */

/**
 * Initializate game
 */
void game_init();

/**
 * Game loop (handles events happening during the game and process them)
 */
void game_loop();

/**
 * Quit game
 */
void game_quit();

/**
 * Refresh game screen
 */
void game_refresh_screen();

/**
 * Handle game events
 *
 * @param SDL_Event *event The event to handles
 */
void game_handle_event(SDL_Event *event);


#endif // GAME_H_INCLUDED