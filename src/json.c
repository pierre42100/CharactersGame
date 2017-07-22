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
    for(int i = 0; i < number_results; i++){

        //Check if the informations provided are for the main character
        if(json_check_two_keys(json_string, &tokens[i], "main_character") == 0){

            //We increase by one
            i++;

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
