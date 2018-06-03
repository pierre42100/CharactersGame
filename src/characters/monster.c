/**
 * Monster source file
 *
 * @author Pierre HUBERT
 */

#include <stdlib.h>

#include "../config.h"
#include "monster.h"
#include "main_character.h"
#include "../core/ui.h"
#include "../core/logging.h"
#include "../core/ui_utils.h"

//Last known monster
static Monster *last_monster = NULL;


void monster_create(int x, int y, int speed){

    //Create a new monster
    Monster *monster = NULL;
    monster = malloc(sizeof(Monster));
    if(monster == NULL)
        fatal_error("Could not allocate memory to create a new monster !");

    //Load the character
    monster->character = character_load(RES_DIRECTORY"bug.png", TEXTURE_MONSTER_CHARACTER);

    //Set monster settings
    monster->character.pos_x = x;
    monster->character.pos_y = y;
    monster->speed = speed;

    //Append the monster to the list
    monster->next = last_monster;
    last_monster = monster;
}

void monster_destroy_all(){

    Monster *curr_monster = NULL;

    while(last_monster != NULL){

        curr_monster = last_monster;
        last_monster = curr_monster->next;
        free(curr_monster);

    }

}

void monster_display_all(){

    //Process the list of monsters
    Monster *curr_monster = last_monster;

    while(curr_monster != NULL){

        //Display the monster
        character_display(&curr_monster->character);

        //Get the next monster
        curr_monster = curr_monster->next;
    }

}

void monster_check_main_character(Character *character){

    //Process the list of monsters
    Monster *curr_monster = last_monster;

    while(curr_monster != NULL){

        //If there is a collision, the main character lose a live.
        if(character_check_collision(character, &curr_monster->character))
            main_character_lose_one_live();

        //Get the next monster
        curr_monster = curr_monster->next;
    }

}

void monsters_move(){

    //Process the list of monsters
    Monster *curr_monster = last_monster;

    while(curr_monster != NULL){

        //Move randomly the character
        int move;
        switch(rand() % 4){
        case 0:
            move = MOVE_CHARACTER_DOWN;
            break;
        case 1:
            move = MOVE_CHARACTER_LEFT;
            break;
        case 2:
            move = MOVE_CHARACTER_RIGHT;
            break;
        default:
            move = MOVE_CHARACTER_UP;
            break;
        }

        for(int i = 0; i < curr_monster->speed; i++)
            character_move(&curr_monster->character, move);

        //Get the next monster
        curr_monster = curr_monster->next;
    }

}

void monster_routine(){

    //Move the monsters
    monsters_move();

    //Check monsters with main characters
    monster_check_main_character(&main_character_get()->character);
}

#include "monster.h"
