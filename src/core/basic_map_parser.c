/**
 * Basic map parser - Source file
 *
 * @author Pierre HUBERT
 */

#include "basic_map_parser.h"

char basic_map_parser_character_type_to_char(const CharacterType type){

    char character;

    switch(type){

        case CROSS:
            character = '1';
            break;

        case HEART:
            character = '2';
            break;

        case MONSTER:
            character = '3';
            break;

        case PIZZA:
            character = '4';
            break;

        case WALL:
            character = '5';
            break;

        default:
            character = '0';
            break;

    }

    return character;

}


CharacterType basic_map_parser_char_to_character_type(const char c){

    CharacterType type;

    switch(c){

        case '1':
            type = CROSS;
            break;

        case '2':
            type = HEART;
            break;

        case '3':
            type = MONSTER;
            break;

        case '4':
            type = PIZZA;
            break;

        case '5':
            type = WALL;
            break;

        default:
            type = NOTHING;
    }

    return type;

}
