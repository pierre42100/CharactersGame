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

/**
 * The map
 */
Map map;

void game_editor_open() {

    log_message(LOG_VERBOSE, "Opening game editor...");

    game_update_state(GAME_STATE_EDITOR);

    cursor = character_load(RES_DIRECTORY"cursor.png", TEXTURE_CURSOR);
    cursor.pos_x = 0;
    cursor.pos_y = 0;

    //Import file (if any)
    map = basic_map_parser_character_load_map(MAP_FILE);
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

/**
 * Display (render) the characters
 */
void display_characters(){
    for(int i = 0; i < GAME_GRID_ROW_COUNT; i++){
        for(int j = 0; j < GAME_GRID_COL_COUNT; j++){

            CharacterType type = map.characters[i][j];

            //Check if there is not anything to be done
            if(type == NOTHING)
                continue;

            //Create a character and display it
            Character character;

            if(type == CROSS)
                 character = character_load(PATH_IMG_CROSS, TEXTURE_CROSS);

            if(type == HEART)
                character = character_load(PATH_IMG_HEART, TEXTURE_HEART_CHARACTER);

            if(type == MONSTER)
                character = character_load(PATH_IMG_MONSTER, TEXTURE_MONSTER_CHARACTER);

            if(type == PIZZA)
                character = character_load(PATH_IMG_PIZZA, TEXTURE_PIZZA);

            if(type == WALL)
                character = character_load(PATH_IMG_WALL, TEXTURE_WALL);

            if(type == MAIN_CHARACTER)
                character = character_load(PATH_IMG_MAIN_CHARACTER, TEXTURE_MAIN_CHARACTER);

            character.pos_x = i;
            character.pos_y = j;
            character_display(&character);

        }
    }
}

void game_editor_display() {

    log_message(LOG_VERBOSE, "Display game editor");

    //Display game grid & characters
    display_grid();
    display_characters();

    //Display cursor
    character_display(&cursor);
}

void process_update_event(SDL_Event *event) {

    //Determine the new type for the case
    CharacterType newType;

    switch(event->key.keysym.sym){

        case SDLK_1:
            newType = CROSS;
            break;

        case SDLK_2:
            newType = HEART;
            break;

        case SDLK_3:
            newType = MONSTER;
            break;

        case SDLK_4:
            newType = PIZZA;
            break;

        case SDLK_5:
            newType = WALL;
            break;

        case SDLK_6:
            basic_map_parser_remove_main_character(&map);
            newType = MAIN_CHARACTER;
            break;

        //Default = nothing
        default:
            newType = NOTHING;
    }

    //Apply new character
    int x = cursor.pos_x;
    int y = cursor.pos_y;
    map.characters[x][y] = newType;
}

void save_map(){

    //Log action
    log_message(LOG_MESSAGE, "Saving new map");

    //Save the map
    FILE* file = fopen(MAP_FILE, "w+");

    if(file == NULL){
        log_message(LOG_ERROR, "Could not open the file!");
        return;
    }

    //Process the map
    for(int i = 0; i < GAME_GRID_ROW_COUNT; i++){
        for(int j = 0; j < GAME_GRID_COL_COUNT; j++){

            //Turn the caracter into an integer and append it to the file
            fputc(basic_map_parser_character_type_to_char(map.characters[i][j]), file);

        }
        fputc('\n', file);
    }

    //Close the file
    fclose(file);
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

                //To update the character in the game
                case SDLK_0:
                case SDLK_1:
                case SDLK_2:
                case SDLK_3:
                case SDLK_4:
                case SDLK_5:
                case SDLK_6:
                    process_update_event(event);
                break;

                //Save the map
                case SDLK_RETURN:
                    save_map();
                break;

                //Pause the game
                case SDLK_ESCAPE:
                    game_update_state(GAME_STATE_MENU);
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
