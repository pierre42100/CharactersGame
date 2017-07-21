#ifndef GAME_MENU_H_INCLUDED
#define GAME_MENU_H_INCLUDED

/**
 * Game menu header file
 */

/**
 * Display game menu
 */
void game_menu_display();

/**
 * Handle game menu events
 *
 * @param SDL_Event *event The event to process
 */
void game_menu_handle_events(SDL_Event *event);

#endif // GAME_MENU_H_INCLUDED
