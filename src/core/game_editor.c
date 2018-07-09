/**
 * Game editor source file
 *
 * @author Pierre HUBERT
 */

#include <SDL2/SDL.h>

#include "../config.h"
#include "ui.h"
#include "logging.h"
#include "game.h"
#include "game_editor.h"

void game_editor_open() {

    log_message(LOG_VERBOSE, "Opening game editor...");

    game_update_state(GAME_STATE_EDITOR);


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
}
