/**
 * Game functions - Header file
 *
 * @author Pierre HUBERT
 */

#include <SDL2/SDL.h>
#include <unistd.h>
#include <pthread.h>

#include "logging.h"
#include "ui.h"
#include "../config.h"
#include "../characters/main_character.h"
#include "../characters/monster.h"
#include "character.h"
#include "game_menu.h"
#include "game_started.h"
#include "game_paused.h"
#include "game_over.h"
#include "game_editor.h"
#include "game.h"

//This variables defines if the application has to be left or not
static int quit_app = 0;

//This variable stores when a window refreshing is required
static int need_window_refresh = 1;

//This variable knows if the games has started or not
static int game_state = GAME_STATE_MENU;

//Game threads
static pthread_t game_routine_thread;

/**
 * Initialize game
 */
void game_init(){

    //Inform about what is happening
    log_message(LOG_VERBOSE, "Initializating application...");

    //Initialize the SDL library
    ui_init();

    //Load the background
    ui_load_background();

    //Create event catcher thread
    if(pthread_create(&game_routine_thread, NULL, game_routine_thread_function, NULL))
        fatal_error("Couldn't create routine thread !");
}


/**
 * Game loop (handles events happening during the game and process them)
 */
void game_loop(){

    //Inform about what is happening
    log_message(LOG_VERBOSE, "Starting game loop...");

    //Refresh game screen
    game_refresh_screen();

    //Event handler
    SDL_Event event;

    //Perpetual loop
    while(1==1){
        //Wait for an event
        SDL_WaitEventTimeout(&event, MAX_PAUSE_BETWEEN_SCREEN_REFRESH*1000);

        //Check if event is "quit game"
        if(event.type == SDL_QUIT)
            game_quit();

        //Handle event
        game_handle_event(&event);

        //Check if we have to quit game
        if(quit_app == 1){
            //Inform user
            log_message(LOG_MESSAGE, "A request has been made to quit the application.");

            break;
        }

        //Check if it is required to refresh screen
        //if(need_window_refresh == 1){
            game_refresh_screen();
            //need_window_refresh = 0;
        //}
    }

}

/**
 * Quit game
 */
void game_quit(){

    //Inform about what is happening
    log_message(LOG_VERBOSE, "Quitting game...");

    //Quit UI
    ui_quit();

    //Exit game
    exit(EXIT_SUCCESS);

}

/**
 * Handle game events
 *
 * @param SDL_Event *event The event to handles
 */
void game_handle_event(SDL_Event *event){

    //Check the current game state and adapt the action to do
    switch(game_state){

        //The game is started
        case GAME_STATE_STARTED:
            game_started_handle_events(event);
        break;

        //The user is in the menu of the application
        case GAME_STATE_MENU:
            game_menu_handle_events(event);
        break;

        //The user has paused the game
        case GAME_STATE_PAUSED:
            game_paused_handle_events(event);
        break;

        //The game is over
        case GAME_STATE_OVER:
            game_over_handles_events(event);
        break;

        //The game is in editor state
        case GAME_STATE_EDITOR:
            game_editor_handles_events(event);
        break;
    }

}

/**
 * Specify wether wether the screen should be updated or not
 *
 * @param int need 1 = yes / 0 = no
 */
void game_screen_to_update(int need){
    need_window_refresh = need == 1 ? 1 : 0;
}

/**
 * Refresh game screen
 */
void game_refresh_screen(){

    //Display game background
    ui_display_background();

    //Check the current game state and adapt the action to do
    switch(game_state){

        //The game is started
        case GAME_STATE_STARTED:
            game_started_refresh_window();
        break;

        //The user is in the menu of the application
        case GAME_STATE_MENU:
            game_menu_display();
        break;

        //The user has paused the game
        case GAME_STATE_PAUSED:
            game_paused_display();
        break;

        //The game is over
        case GAME_STATE_OVER:
            game_over_display();
        break;

        //The game editor is opened
        case GAME_STATE_EDITOR:
            game_editor_display();
        break;
    }

    //Refresh the screen
    ui_refresh_window();

}

/**
 * Update game state
 *
 * @param int new_state The new state of the game
 */
void game_update_state(int new_state){
    game_state = new_state;
}

/**
 * Get game state
 *
 * @return int The state of the game
 */
int game_get_state(){
    return game_state;
}

/**
 * Game routine thread
 *
 * @param *void Nothing
 */
void *game_routine_thread_function(void *param){

    //Avoid errors
    (void) param;

    //Perform a loop
    while(1 == 1){

        //Routines are performed only if the game is started
        if(game_state == GAME_STATE_STARTED){

            //Log action
            log_message(LOG_VERBOSE, "Perform game routine");

            //Call game routines

            //Monsters routine
            monster_routine();
        }

        //Make a pause
        usleep(PAUSE_BETWEEN_GAME_ROUTINES * 50000);

    }


    //Close thread
    pthread_exit(EXIT_SUCCESS);

}
