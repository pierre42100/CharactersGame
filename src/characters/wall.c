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
 * Destroy all the walls
 *
 * @return void
 */
void wall_destroy_all(){

    //Declare variables
    Wall *curr_wall = NULL;

    //Check if there isn't any wall to destroy
    if(last_wall == NULL)
        return; //Nothing to be done

    //Else process each wall to delete them
    curr_wall = last_wall;
    while(last_wall != NULL){

        //Save the next wall reference
        last_wall = curr_wall->nextWall;

        //Delete the current wall (free memory)
        free(curr_wall);

        curr_wall = last_wall;

    }

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

/**
 * Check if a character is on a wall or not
 *
 * @param Character *character The character to check
 * @return int 1 = Yes, the character is on a wall / 0 = No, the character isn't on a wall
 */
int wall_check_character_presence(Character *character){

    //Declare variables
    Wall *curr_wall = NULL;

    //Check if at least one character exists before
    if(last_wall == NULL)
        return 0; //There isn't any wall

    //Process all the walls
    curr_wall = last_wall;
    while(curr_wall != NULL){

        //Check wall
        if(character_check_collision(character, &curr_wall->character) != 0)
            return 1; //There is a collision

        //Get the next wall memory address
        curr_wall = curr_wall->nextWall;

    }

    //If we get there, there isn't any collision
    return 0;

}
