/**
 * UI functions - Source file
 *
 * This file handle the main graphical operations
 *
 * @author Pierre HUBERT
 */

#include <SDL2/SDL.h>

#include "logging.h"
#include "config.h"

/**
 * Variables definition
 */
static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;


/**
 * Initializate the SDL library plus create programm windows & renderer
 */
void ui_init(){

    //Initializate SDL
    if(SDL_Init(SDL_INIT_VIDEO) != 0)
        fatal_error("Couldn't initializate the SDL2.0 Library !");


    //Create window
    window = SDL_CreateWindow(GAME_NAME, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGH, SDL_WINDOW_SHOWN);

    //Check if the window was successfully created
    if(window == NULL)
        fatal_error("Couldn't create programm window !");

    //Create renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    //Check if the operation failed
    if(renderer == NULL){
        log_message(LOG_ERROR, "Couldn't create a renderer based on accelarated way. Falling back to software renderer.");
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    }

    //Check if not any renderer could be created
    if(renderer == NULL){
        //This time it is a fatal error
        fatal_error("Couldn't create a renderer (tryed both accelerated & software renderer) !");
    }

    //End of function
    return;
}

/**
 * Terminate and close UI
 */
void ui_quit(){

    //Message
    log_message(LOG_VERBOSE, "Terminate UI.");

    //Destroy renderer (if it exists)
    if(renderer != NULL)
        SDL_DestroyRenderer(renderer);

    //Destroy window (if it exists)
    if(window != NULL){
        SDL_DestroyWindow(window);
    }

    //Quit SDL
    SDL_Quit();

    //End of function
    return;
}
