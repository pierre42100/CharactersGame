#ifndef LOGGING_H_INCLUDED
#define LOGGING_H_INCLUDED

/**
 * Logging functions - Header file
 *
 * @author Pierre HUBERT
 */

/**
 * Logging flags
 */
#define LOG_VERBOSE 0
#define LOG_MESSAGE 1
#define LOG_ERROR 2
#define LOG_FATAL_ERROR 3

/**
 * Log a message (can be anything)
 *
 * @param int flag Flags pointing on the logging level
 * @param const char *message The message to log
 * @return void
 */
void log_message(int flag, const char *message);

/**
 * Handle fatal errors
 *
 * @param const char *message The message of the fatal error
 * @return void (The programm quit before the end of the function)
 */
void fatal_error(const char *message);

#endif // LOGGING_H_INCLUDED
