/**
 * JSON functions - Functions file
 *
 * @author Pierre HUBERT
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lib/jsmn/jsmn.h"

#include "logging.h"
#include "utils.h"
#include "json.h"
#include "characters/main_character.h"

/**
 * Parse game JSON file
 *
 * @param const char *filename The name of the file to parse
 */
void json_parse_game_file(const char *filename){

    //Declare required variables
    char *json_content = NULL;
    jsmn_parser parser;
    jsmntok_t *tokens = NULL;
    int error = 0, nb_results = 0;
    int number_tokens = 10; //Let's suppose there'll be only 100 tokens

    //Log action
    log_message(LOG_MESSAGE, "Parsing a game file");

    //Get the file content
    file_get_contents(&json_content, filename);

    //Initializate parser
    jsmn_init(&parser);

    //Parse JSON file
    do{
        //Log action
        log_message(LOG_VERBOSE, "Allocate memory for JSON tokens.");

        //If memory hasn't been allocated yet
        if(tokens == NULL)
            tokens = malloc(number_tokens*sizeof(*tokens));

        //Reallocate memory else
        else{

            //Add ten entries
            number_tokens += 10;

            tokens = realloc(tokens, number_tokens*sizeof(jsmntok_t));
        }

        //Check if memory hasn't been allocated
        if(tokens == NULL)
            fatal_error("Couldn't allocate memory to store JSON tokens !");

        //Try to parse JSON file
        error = jsmn_parse(&parser, json_content, strlen(json_content), tokens, number_tokens);

        //Check if JSON code is too large
        if(number_tokens > 10000)
            break; //Break loop, else we will encounter memory problems

    } while(error == JSMN_ERROR_NOMEM);

    //Check for errors during decoding
    if(error == JSMN_ERROR_INVAL){
       fatal_error("JSON code is invalid !");
    }
    if(error == JSMN_ERROR_NOMEM){
       fatal_error("JSON code is too large !");
    }
    if(error == JSMN_ERROR_PART){
       fatal_error("JSON code is too short !");
    }

    //Check for other errors
    if(error < 0){
        fatal_error("An uknow error occured while trying to decode JSON!");
    }

    //Now we can read JSON code
    nb_results = error;

    //Check the result can be processed
    if(nb_results < 1 || tokens[0].type != JSMN_OBJECT)
        fatal_error("Excepted JSON object at the root of the json file !");

    //Process results
    json_parse_results(&parser, tokens, nb_results, json_content);

    //Free memory
    free(tokens);
    free(json_content);
}

/**
 * Parse JSON results
 *
 * @param jsmn_parser *parser The parser associated to the results
 * @param jsmntok_t *tokens The tokens results
 * @param int number_results The number of results
 * @param const char *json_string The JSON string to use
 * @return void
 */
void json_parse_results(jsmn_parser *parser, jsmntok_t *tokens, int number_results, const char *json_string){

    //Process each token
    for(int i = 1; i < number_results; i++){ //i = 1 because Root object has not to be processed

        //Check if the informations provided are for the main character
        if(json_check_two_keys(json_string, &tokens[i], "main_character") == 0){

            //If the next item isn't an object we report an error
            if(tokens[i+1].type != JSMN_OBJECT){
                log_message(LOG_ERROR, "Object excepted after token 'main_character' !");

                continue;
            }

            //Update main counter
            i++; //To upgrade to main_character object (that contains other properties)

            //Process each property
            int object_tokens_number = tokens[i].size;
            for(int j = 1; j <= object_tokens_number; j++){

                //Check if we have to update main character coordinates
                if(json_check_two_keys(json_string, &tokens[i+j], "pos_x") == 0 && tokens[i+j+1].type == JSMN_PRIMITIVE){

                    //Retrieve the value
                    int pos_x = json_extract_integer(json_string, &tokens[i+j+1]);

                    //We have to update x coordinate of the object
                    main_character_set_pos_x(pos_x);
                    printf("Update pos_x: %d\n", pos_x);

                }
                //Check if we have to update main character coordinates
                else if(json_check_two_keys(json_string, &tokens[i+j], "pos_y") == 0 && tokens[i+j+1].type == JSMN_PRIMITIVE){

                    //Retrieve the value
                    int pos_y = json_extract_integer(json_string, &tokens[i+j+1]);

                    //We have to update x coordinate of the object
                    main_character_set_pos_y(pos_y);
                    printf("Update pos_y: %d\n", pos_y);

                }
                else {
                    //Error
                    log_message(LOG_ERROR, "A child of the main_character object was not understood !");
                    printf("j=%d\ntokens-size: %d\n%.*s\n",j, object_tokens_number, tokens[i+j].end - tokens[i+j].start, json_string + tokens[i+j].start);
                }

                //Increase counter (to count the secondary value)
                i++;

            }

            //Update main counter
            i += object_tokens_number; //For all the key name of the object

        }
        else {
            log_message(LOG_ERROR, "A JSON key was not understood...");
        }

    }

}


/**
 * Check if a JSON key value correspond to a specified JSON key value
 *
 * @param const char *json_string The JSON string to use
 * @param jsmntok_t *tok The token to check
 * @param const char *key_value The value of the key
 * @return int 0 = The two keys are the same / -1 = The keys are different
 */
int json_check_two_keys(const char *json_string, jsmntok_t *tok, const char *key_value){
    return (

        tok->type == JSMN_STRING && //Check token type
        (int) strlen(key_value) == tok->end - tok->start && //Check string size
        strncmp(json_string + tok->start, key_value, tok->end - tok->start) == 0 //Check string value

    ) ? 0 : -1;
}

/**
 * Retrieve an integer of a JSON chain related to a specified key
 *
 * @param const char *json_string The source JSON string
 * @param jsmntok_t *tok The reference tokn
 * @return int -1 in case of failure / Specified number else
 */
int json_extract_integer(const char *json_string, jsmntok_t *token){

    //Declare variables
    char *string = NULL;
    int number = -1;

    //Check the current key is a primitive integer
    if(token->type != JSMN_PRIMITIVE)
        return -1; //The operation can't succeed

    //Allocate memory
    string = malloc(((token->end)-(token->start)+1)*sizeof(char));

    if(string == NULL)
        fatal_error("Couldn't allocate memory for a string !");

    //Extract the key value and convert it into an integer
    strncpy(string, json_string + token->start, token->end - token->start);
    string[token->end - token->start] = '\0'; //Make sure the string is ended correctly
    number = atoi(string);

    //Free memory
    free(string);

    //Return result
    return number;

}
