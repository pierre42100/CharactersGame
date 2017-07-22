#ifndef JSON_H_INCLUDED
#define JSON_H_INCLUDED

/**
 * JSON functions - Header file
 *
 * @author Pierre HUBERT
 */

#include "lib/jsmn/jsmn.h"

/**
 * Parse game JSON file
 *
 * @param const char *filename The name of the file to parse
 */
void json_parse_game_file(const char *filename);

/**
 * Parse JSON results
 *
 * @param jsmn_parser *parser The parser associated to the results
 * @param jsmntok_t *tokens The tokens results
 * @param int number_results The number of results
 * @param const char *json_string The JSON string to use
 * @return void
 */
void json_parse_results(jsmn_parser *parser, jsmntok_t *tokens, int number_results, const char *json_string);

/**
 * Check if a JSON key value correspond to a specified JSON key value
 *
 * @param const char *json_string The JSON string to use
 * @param jsmntok_t *tok The token to check
 * @param const char *key_value The value of the key
 * @return int 0 = The two keys are the same / -1 = The keys are different
 */
int json_check_two_keys(const char *json_string, jsmntok_t *tok, const char *key_value);

#endif // JSON_H_INCLUDED
