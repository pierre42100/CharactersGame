/**
 * Some utilities - Source file
 *
 * @author Pierre HUBERT
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "logging.h"
#include "utils.h"

/**
 * Get a file contents
 *
 * @param char **targetString The target string
 * @param const char *filename The file to get the content from
 * @return int 0 = success / -1 = error
 */
int file_get_contents(char **targetString, const char *filename){

    //Create required variables
    FILE *file = NULL;
    int file_length = 0;
    char currChar = 0;
    char *file_content = NULL;

    //First, open the file (in read-only mode)
    file = fopen(filename, "r");

    if(file == NULL){
        //Couldn't open required file
        log_message(LOG_ERROR, "Couldn't open required file!");
        return -1;
    }

    //Determine file length
    file_length = (int) determine_file_length(file);

    //Allocate memory to read file
    *targetString = malloc((file_length+1)*sizeof(char));
    file_content = *targetString;

    //Check the memory was allocated
    if(file_content == NULL){
        fatal_error("Couldn't allocate memory for file_content in file_get_contents !");
    }

    //Place file cursor at the begining of the file
    fseek(file, 0, SEEK_SET);

    //Read the content of the file
    for(int i = 0; i < file_length; i++){
        currChar = fgetc(file);

        //Check if it is an EOF character
        if(currChar == EOF){
            file_content[i] = '\0';
            break;
        }

        //Else we can write the new character
        file_content[i] = currChar;
    }

    //Add a '\0' at the end of the string
    file_content[file_length] = '\0';

    //Close the file
    fclose(file);

    //Log action
    log_message(LOG_VERBOSE, "Terminated to read a file.");

    //The operation is a success
    return 0;

}

/**
 * Determine a file length
 *
 * @param FILE *file The file to determine the lenght
 * @return long The length of the file
 */
long determine_file_length(FILE *file){

    //Declare variables
    long curpos, file_length;

    //Get current cursor position
    curpos = ftell(file);

    //Place cursor at the end of the file
    fseek(file, 0, SEEK_END);

    //Get the file length
    file_length = ftell(file);

    //Place the cursor at its old position
    fseek(file, curpos, SEEK_SET);

    //Return the result
    return file_length;

}
