/**
 * Game editor source file
 *
 * @author Pierre HUBERT
 */

#include <SDL2/SDL.h>

#include "character.h"
#include "../config.h"
#include "ui.h"
#include "ui_utils.h"
#include "logging.h"
#include "game.h"
#include "game_editor.h"

/**
 * Cursor character
 */
Character cursor;

void game_editor_open() {

    log_message(LOG_VERBOSE, "Opening game editor...");

    game_update_state(GAME_STATE_EDITOR);

    cursor = character_load(RES_DIRECTORY"cursor.png", TEXTURE_CURSOR);
    cursor.pos_x = 0;
    cursor.pos_y = 0;
}

/**
 * Display game editor grid
 */
void display_grid() {

    //Set color
    SDL_SetRenderDrawColor(ui_get_renderer(), 0,0,0,1);

    //Display horizontal lines
    for(int height = GAME_GRID_Y_POSITION; height < WINDOW_HEIGHT; height += GAME_CELL_HEIGHT){
        //Draw an horizontal line
        SDL_RenderDrawLine(ui_get_renderer(), GAME_GRID_X_POSITION, height, WINDOW_WIDTH, height);
    }

    //Display vertical lines
    for(int width = GAME_GRID_X_POSITION; width < WINDOW_WIDTH; width += GAME_CELL_WIDTH)
        SDL_RenderDrawLine(ui_get_renderer(), width, GAME_GRID_Y_POSITION, width, WINDOW_HEIGHT);

}

void game_editor_display() {

    log_message(LOG_VERBOSE, "Display game editor");

    //Display game grid
    display_grid();

    //Display cursor
    character_display(&cursor);
}

void game_editor_handles_events(SDL_Event *event) {

    //Determine the nature of the current event
    switch(event->type){

        //Check if it is a keyboard eventd
        case SDL_KEYDOWN:

            //The window will certainly need to be refreshed
            game_screen_to_update(1);

            switch(event->key.keysym.sym){

                //To go right
                case SDLK_RIGHT:
                case SDLK_d:
                    character_move(&cursor, MOVE_CHARACTER_RIGHT);
                break;

                //To go left
                case SDLK_LEFT:
                case SDLK_q:
                    character_move(&cursor, MOVE_CHARACTER_LEFT);
                break;

                //To go up
                case SDLK_UP:
                case SDLK_z:
                    character_move(&cursor, MOVE_CHARACTER_UP);
                break;

                //To go down
                case SDLK_DOWN:
                case SDLK_w:
                    character_move(&cursor, MOVE_CHARACTER_DOWN);
                break;

                //Pause the game
                case SDLK_ESCAPE:
                case SDLK_p:

                break;

            }
        break;

        //To quit the game
        case SDL_QUIT:
            //Change quit variable to true
            game_quit();
        break;

    }

}
