#ifndef GAME_PAUSED_H_INCLUDED
#define GAME_PAUSED_H_INCLUDED

/**
 * Game pause management - Header file
 *
 * @author Pierre HUBERT
 */

/**
 * Makes game pause
 */
void game_paused_pause();

/**
 * Resume the game
 */
void game_paused_resume();

/**
 * Display game pause menu
 */
void game_paused_display();

/**
 * Handle game menu events
 *
 * @param SDL_Event *event The event to process
 */
void game_paused_handle_events(SDL_Event *event);

#endif // GAME_PAUSED_H_INCLUDED
