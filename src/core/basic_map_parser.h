/**
 * Basic map parser - Header file
 *
 * @author Pierre HUBERT
 */

#ifndef BASIC_MAP_PARSER_H_INCLUDED
#define BASIC_MAP_PARSER_H_INCLUDED

#include "../config.h"

/**
 * Characters type
 */
enum character_type {
    NOTHING,
    CROSS,
    HEART,
    MONSTER,
    PIZZA,
    WALL,
    MAIN_CHARACTER
};
typedef enum character_type CharacterType;

/**
 * Map structure
 */
typedef struct Map {

    //The list of characters in the map
    CharacterType characters[GAME_GRID_ROW_COUNT][GAME_GRID_COL_COUNT];

} Map;

/**
 * Transform a CharacterType variable into a char
 *
 * @param const CharacterType type The type of character to transform
 * @return char Generated char object
 */
char basic_map_parser_character_type_to_char(const CharacterType type);

/**
 * Transform a char into a CharacterType variable
 *
 * @param const char c The character to transform
 * @return CharacterType Generated character type
 */
CharacterType basic_map_parser_char_to_character_type(const char c);

/**
 * Load a map file into Map structure
 *
 * @param const char *filename The path to the map file
 * @return Map Generated map structure
 */
Map basic_map_parser_character_load_map(const char *filename);

/**
 * Parse specified map file to create game map
 *
 * @param const char *filename The name of the file to parse
 */
void basic_map_parser_parse_map(const char *filename);

/**
 * Remove the main character from a map
 *
 * @param Map *map The map to process
 */
void basic_map_parser_remove_main_character(Map *map);

#endif // BASIC_MAP_PARSER_H_INCLUDED
