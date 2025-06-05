/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** logger
** Created by Martin BONTE
** This File is part of a custom independent library written entirely by me.
** All logic, design, and implementation choices are my own work.
*/

#ifndef LOGGER_H
    #define LOGGER_H

#ifdef __cplusplus
    extern "C" {
#endif

    #include <stdbool.h>

    typedef enum {
        CONSOLE,
        FILE_OUTPUT,
        BOTH
    } output_t;

/**
 * @brief Log an info message with the current time.
 *
 * This function logs the message with the current time.
 * @param message The message to log.
 * @param output The output destination for the log (Console, File, or Both).
 * @param date Whether to include the current date in the log message.
 * @return true if the log was successful, false otherwise.
 */
    bool logger_info(char *message, output_t output, bool date);

/**
 * @brief Log a debug message with the current time.
 *
 * This function logs the message with the current time.
 * @param message The message to log.
 * @param output The output destination for the log (Console, File, or Both).
 * @param date Whether to include the current date in the log message.
 * @return true if the log was successful, false otherwise.
 */
    bool logger_debug(char *message, output_t output, bool date);

/**
 * @brief Log a warning message with the current time.
 *
 * This function logs the message with the current time.
 * @param message The message to log.
 * @param output The output destination for the log (Console, File, or Both).
 * @param date Whether to include the current date in the log message.
 * @return true if the log was successful, false otherwise.
 */
    bool logger_warning(char *message, output_t output, bool date);

/**
 * @brief Clear the log File.
 *
 * This function clears the log File by truncating it.
 */
    bool logger_clear_log_file(void);

    #ifdef __cplusplus
}
    #endif

#endif
