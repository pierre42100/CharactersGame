#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

/**
 * Game functions - Header file
 *
 * @author Pierre HUBERT
 */

#include <SDL2/SDL.h>

/**
 * Define game states
 */
#define GAME_STATE_MENU 0
#define GAME_STATE_STARTED 1
#define GAME_STATE_PAUSED 2
#define GAME_STATE_OVER 3


/**
 * Initializate game
 */
void game_init();

/**
 * Update game state
 *
 * @param int new_state The new state of the game
 */
void game_update_state(int new_state);

/**
 * Get game state
 *
 * @return int The state of the game
 */
int game_get_state();

/**
 * Game loop (handles events happening during the game and process them)
 */
void game_loop();

/**
 * Quit game
 */
void game_quit();

/**
 * Specify wether wether the screen should be updated or not
 *
 * @param int need 1 = yes / 0 = no
 */
void game_screen_to_update(int need);

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

/**
 * Game routine thread function
 *
 * @param *void Nothing
 */
void *game_routine_thread_function(void *param);


#endif // GAME_H_INCLUDED
