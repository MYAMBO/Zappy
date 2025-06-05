/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** logger
*/

#include "logger.h"

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void get_timestamp(char *buffer, size_t size, bool date)
{
    time_t now = time(NULL);
    struct tm *t = localtime(&now);

    if (!date) {
        buffer[0] = '\0';
        return;
    }
    strftime(buffer, size, "[%Y-%m-%d %H:%M:%S] ", t);
}

bool logger_log(const char *prefix, char *message, output_t out, bool date)
{
    FILE *file;
    char time[32];

    if (!message || !prefix)
        return false;
    get_timestamp(time, sizeof(time), date);
    if (out == CONSOLE || out == BOTH)
        printf("%s%s%s\n", time, prefix, message);
    if (out == FILE_OUTPUT || out == BOTH) {
        file = fopen("debug.log", "a");
        if (!file)
            return false;
        fprintf(file, "%s%s%s\n", time, prefix, message);
        fclose(file);
    }
    return true;
}

bool logger_info(char *message, output_t output, bool date)
{
    return logger_log("[INFO] ", message, output, date);
}

bool logger_debug(char *message, output_t output, bool date)
{
    return logger_log("[DEBUG] ", message, output, date);
}

bool logger_warning(char *message, output_t output, bool date)
{
    return logger_log("[WARNING] ", message, output, date);
}

bool logger_clear_log_file(void)
{
    FILE *file = fopen("debug.log", "w");

    if (!file)
        return false;
    fclose(file);
    return true;
}
