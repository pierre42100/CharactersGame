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

//Game window
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 608

//Game grid
#define GAME_CELL_WIDTH 32
#define GAME_CELL_HEIGHT 32

#define GAME_NB_CELL_X_AXIS 25
#define GAME_NB_CELL_Y_AXIS 19

//Pause between two games routines execution
#define PAUSE_BETWEEN_GAME_ROUTINES 0.5
#define MAX_PAUSE_BETWEEN_SCREEN_REFRESH 2

#endif // CONFIG_H_INCLUDED
