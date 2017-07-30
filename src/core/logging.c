/**
 * Logging functions - Source file
 *
 * @author Pierre HUBERT
 */

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

#include "logging.h"
#include "game.h"

/**
 * Log a message (can be anything)
 *
 * @param int flag Flags pointing on the logging level
 * @param const char *message The message to log
 * @return void
 */
void log_message(int flag, const char *message){

    //Process the message differently depending of what is it
    switch(flag){

        //Verbose message
        case LOG_VERBOSE:
        fprintf(stdout, "Verbose: %s\n", message);
        break;

        //In case of error
        case LOG_ERROR:
        fprintf(stderr, "Error: %s\n", message);
        fprintf(stderr, "SDL2.0 Error: %s\n", SDL_GetError());
        break;

        //In case of fatal error
        case LOG_FATAL_ERROR:
            //Display errors
            fprintf(stderr, "Fatal Error: %s\n", message);
            fprintf(stderr, "SDL2.0 Error: %s\n", SDL_GetError());
        break;

        //Simple message
        case LOG_MESSAGE:
        default: //This is the default message type
        fprintf(stdout, "Message: %s\n", message);
        break;
    }

    //End of function
    return;

}

/**
 * Handle fatal errors
 *
 * @param const char *message The message of the fatal error
 * @return void (The programm quit before the end of the function)
 */
void fatal_error(const char *message){
    //Display message error
    log_message(LOG_FATAL_ERROR, message);

    //Quit game
    game_quit();

    //Close programm
    exit(EXIT_FAILURE);
}
