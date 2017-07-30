#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

/**
 * Some utilities - Header file
 *
 * @author Pierre HUBERT
 */

/**
 * Get a file contents
 *
 * @param char *targetString The target string
 * @param const char **filename The file to get the content from
 * @return int 0 = success / -1 = error
 */
int file_get_contents(char **targetString, const char *filename);

/**
 * Determine a file length
 *
 * @param FILE *file The file to determine the lenght
 * @return long The length of the file
 */
long determine_file_length(FILE *file);

#endif // UTILS_H_INCLUDED
