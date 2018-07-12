/**
 * Basic map parser - Source file
 *
 * @author Pierre HUBERT
 */

#include <stdio.h>

#include "basic_map_parser.h"
#include "logging.h"

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

Map basic_map_parser_character_load_map(const char *filename){

    Map map;

    //Reset map table
    for(int i = 0; i < GAME_GRID_ROW_COUNT; i++){
        for(int j = 0; j < GAME_GRID_COL_COUNT; j++)
            map.characters[i][j] = NOTHING;
    }

    //Try to open the file
    FILE* file = fopen(filename, "r");
    if(!file){
        log_message(LOG_ERROR, "Could not open map file!");
        return map;
    }

    //Parse it
    char c = fgetc(file);

    int x = 0;
    int y = 0;

    while(c != EOF){

        if(c == '\n'){
            x++;
            y = 0;
        }

        else {

            //Save new character
            map.characters[x][y] = basic_map_parser_char_to_character_type(c);
            y++;
        }

        //Read a new character
        c = fgetc(file);
    }

    //Close the file
    fclose(file);

    return map;
}

void basic_map_parser_parse_map(const char *filename){



}
