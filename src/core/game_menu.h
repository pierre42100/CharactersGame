#ifndef GAME_MENU_H_INCLUDED
#define GAME_MENU_H_INCLUDED

/**
 * Game menu header file
 */

 /**
  * Menu options IDs
  */
#define MENU_OPTION_START_GAME 1
#define MENU_OPTION_EDITOR 2
#define MENU_OPTION_QUIT_GAME 3

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
