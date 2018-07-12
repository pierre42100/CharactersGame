/**
 * Basic map parser - Header file
 *
 * @author Pierre HUBERT
 */

#ifndef BASIC_MAP_PARSER_H_INCLUDED
#define BASIC_MAP_PARSER_H_INCLUDED

/**
 * Characters type
 */
enum character_type {
    NOTHING,
    CROSS,
    HEART,
    MONSTER,
    PIZZA,
    WALL
};
typedef enum character_type CharacterType;

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
#endif // BASIC_MAP_PARSER_H_INCLUDED
