#ifndef GAME_EDITOR_H_INCLUDED
#define GAME_EDITOR_H_INCLUDED

/**
 * Game editor header file
 *
 * @author Pierre HUBERT
 */

 /**
  * Characters type
  */
enum character_type {
    NOTHING,
    CROSS,
    HEART,
    MONSTER,
    PIZZA,
    WALL
};
typedef enum character_type CharacterType;

/**
 * Open game editor
 */
void game_editor_open();

/**
 * Display current game editor state
 */
void game_editor_display();

/**
 * Handles game events
 *
 * @param SDL_Event *event The event to handles
 */
void game_editor_handles_events(SDL_Event *event);

#endif // GAME_EDITOR_H_INCLUDED
