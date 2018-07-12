#ifndef CONFIG_H_INCLUDED
#define CONFIG_H_INCLUDED

/**
 * Project central configuration
 *
 * @author Pierre HUBERT
 */

//Game main informations
#define GAME_NAME "Simple character game"

//Ressources directory
#define RES_DIRECTORY "res/"

//Main font
#define FONT_FILE "res/UbuntuMono-B.ttf"
#define FONT_PTSIZE 34 //Size of the font to load

//Game window
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

//Game grid
#define GAME_CELL_WIDTH 32
#define GAME_CELL_HEIGHT 31

#define GAME_NB_CELL_X_AXIS 25
#define GAME_NB_CELL_Y_AXIS 19

#define GAME_GRID_X_POSITION 0
#define GAME_GRID_Y_POSITION 14

//Pause between two games routines execution
#define PAUSE_BETWEEN_GAME_ROUTINES 5
#define MAX_PAUSE_BETWEEN_SCREEN_REFRESH 1

//Some useful macros to save time
#define GAME_GRID_WIDTH WINDOW_WIDTH - GAME_GRID_X_POSITION
#define GAME_GRID_HEIGHT WINDOW_HEIGHT - GAME_GRID_Y_POSITION
#define GAME_GRID_ROW_COUNT (GAME_GRID_WIDTH+(GAME_CELL_WIDTH-1))/(GAME_CELL_WIDTH)
#define GAME_GRID_COL_COUNT (GAME_GRID_HEIGHT+(GAME_CELL_HEIGHT-1))/(GAME_CELL_HEIGHT)

#endif // CONFIG_H_INCLUDED
