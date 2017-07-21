/**
 * Character Move - a programm that makes a character move
 *
 * This programm is licensed under the MIT licence
 *
 * @author Pierre HUBERT
 */

#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>

#include "config.h"
#include "ui.h"
#include "game.h"
#include "logging.h"

/**
 * Main function of the programm
 */
int main(){

    //Welcome message
    log_message(LOG_MESSAGE, "Character Move - a simple character moving analysis");
    log_message(LOG_MESSAGE, "(c) Copyright Pierre HUBERT 2017\n");

    //Initializate game
    game_init();

    //Game loop
    game_loop();

    //Quit game
    game_quit();

    //Programm execution is a success
    return EXIT_SUCCESS;
}
