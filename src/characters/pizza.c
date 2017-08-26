/**
 * Pizza object - Source file
 *
 * @author Pierre HUBERT
 */

#include "../config.h"
#include "../core/logging.h"
#include "../core/ui.h"
#include "../core/ui_utils.h"
#include "../core/character.h"

#include "pizza.h"

/**
 * Variables definition
 */
//Address of the last pizza character
static Pizza *last_pizza = NULL;

/**
 * Create a pizza character
 *
 * @param int x
 * @param int y > Coordinates of the first point of the pizza character element
 * @return void
 */
void pizza_create(int x, int y){

    //Declare variables
    Pizza *new_pizza = NULL;

    //Allocate memory for the pizza character
    new_pizza = malloc(sizeof(Pizza));

    //Check for errors
    if(new_pizza == NULL)
        fatal_error("Couldn't allocate memory for the new pizza !");

    //Load the character
    new_pizza->character = character_load(RES_DIRECTORY"pizza.png", TEXTURE_PIZZA);

    //Check if it isn't the first pizza of the list
    if(new_pizza != NULL){
        //Add the new pizza character address to the last pizza character item of the list
        new_pizza->nextPizza = last_pizza;
    }
    else {
        new_pizza->nextPizza = NULL;
    }

    //Replace the last item of the list with the new pizza character
    last_pizza = new_pizza;

    //Update pizza character coordinates
    new_pizza->character.pos_x = x;
    new_pizza->character.pos_y = y;
}

/**
 * Destroy all the pizza characters
 *
 * @return void
 */
void pizza_destroy_all(){

    //Declare variables
    Pizza *curr_pizza = NULL;

    //Check if there isn't any pizza character to destroy
    if(last_pizza == NULL)
        return; //Nothing to be done

    //Else process each pizza character to delete them
    curr_pizza = last_pizza;
    while(last_pizza != NULL){

        //Save the next pizza character reference
        last_pizza = curr_pizza->nextPizza;

        //Delete the current pizza character (free memory)
        free(curr_pizza);

        curr_pizza = last_pizza;

    }

}


/**
 * Display the pizzaes
 *
 * @return void
 */
void pizza_display_all(){

    //Declare variables
    Pizza *curr_pizza = NULL;

    //Check if there is at least one pizza character
    if(last_pizza == NULL)
        return; //Nothing to be done


    //Process all the pizzas
    curr_pizza = last_pizza;
    while(curr_pizza != NULL){

        //Display the pizza character
        character_display(&curr_pizza->character);

        //Get the next pizza character memory address
        curr_pizza = curr_pizza->nextPizza;

    }
}

/**
 * Check if a character is on a pizza character or not
 *
 * @param Character *character The character to check
 * @return int 1 = Yes, the character is on a pizza character / 0 = No, the character isn't on a pizza character
 */
int pizza_check_character_presence(Character *character){

    //Declare variables
    Pizza *curr_pizza = NULL;

    //Check if at least one character exists before
    if(last_pizza == NULL)
        return 0; //There isn't any pizza character

    //Process all the pizzas
    curr_pizza = last_pizza;
    while(curr_pizza != NULL){

        //Check pizza character
        if(character_check_collision(character, &curr_pizza->character) != 0)
            return 1; //There is a collision

        //Get the next pizza character memory address
        curr_pizza = curr_pizza->nextPizza;

    }

    //If we get there, there isn't any collision
    return 0;

}
