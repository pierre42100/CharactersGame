/**
 * Wall object - Source file
 *
 * @author Pierre HUBERT
 */

#include <stdio.h>
#include <stdlib.h>

#include "../config.h"
#include "../logging.h"
#include "../character.h"
#include "../ui.h"
#include "wall.h"

/**
 * Variables definition
 */
//Address of the last wall
static Wall *last_wall = NULL;

/**
 * Create a wall
 *
 * @param int x
 * @param int y > Coordinates of the first point of the wall element
 * @return void
 */
void wall_create(int x, int y){

    //Declare variables
    Wall *new_wall = NULL;

    //Allocate memory for the wall
    new_wall = malloc(sizeof(Wall));

    //Load the character
    new_wall->character = character_load(RES_DIRECTORY"wall.png", TEXTURE_WALL);

    //Check for errors
    if(new_wall == NULL)
        fatal_error("Couldn't allocate memory for the new wall !");

    //Check if it isn't the first wall of the list
    if(last_wall != NULL){
        //Add the new wall address to the last wall item of the list
        new_wall->nextWall = last_wall;
    }
    else {
        new_wall->nextWall = NULL;
    }

    //Replace the last item of the list with the new wall
    last_wall = new_wall;

    //Update wall coordinates
    new_wall->character.pos_x = x;
    new_wall->character.pos_y = y;
}


/**
 * Display the walls
 *
 * @return void
 */
void wall_display_all(){

    //Declare variables
    Wall *curr_wall = NULL;

    //Check if there is at least one wall
    if(last_wall == NULL)
        return; //Nothing to be done


    //Process all the walls
    curr_wall = last_wall;
    while(curr_wall != NULL){

        //Display the wall
        character_display(&curr_wall->character);

        //Get the next wall memory address
        curr_wall = curr_wall->nextWall;

    }
}
