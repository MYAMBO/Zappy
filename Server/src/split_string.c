/*
** EPITECH PROJECT, 2025
** split_string.c
** File description:
** split_string.c
** created and edited by antoiix.
** All rights reserved
*/

#include "split_string.h"

#include "garbage.h"

int is_alphanum(char c, char *str)
{
    for (int i = 0; i != (int)strlen(str); i++) {
        if (c == str[i])
            return 0;
    }
    return 1;
}

int words(char const *str, char *pattern)
{
    int sep_bef = 1;
    int nb_words = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        if (is_alphanum(str[i], pattern) == 1 && sep_bef == 1) {
            sep_bef = 0;
            nb_words++;
        }
        if (is_alphanum(str[i], pattern) == 0 && sep_bef == 0) {
            sep_bef = 1;
        }
    }
    return nb_words;
}

int nb_c_w(char const *str, int i, char *pattern)
{
    int sep_bef = 1;
    int nb_char = 0;

    for (; str[i] != '\0'; i++) {
        if (is_alphanum(str[i], pattern) == 1) {
            sep_bef = 0;
            nb_char++;
        }
        if (is_alphanum(str[i], pattern) == 0 && sep_bef == 0) {
            return nb_char;
        }
    }
    return nb_char;
}

int nb_spaces(char const *str, int i, char *pattern)
{
    int j = 0;

    for (; str[i] != '\0'; i++) {
        if (is_alphanum(str[i], pattern) == 1) {
            return j;
        }
        j++;
    }
    return j;
}

char **split_string(char const *str, char *pattern)
{
    int i = 0;
    int j = 0;
    int k = 0;
    int nb_words = words(str, pattern);
    char **array = my_malloc(sizeof(char *) * (nb_words + 1));

    if (array == NULL)
        return NULL;
    for (; i != nb_words; i++) {
        array[i] = my_malloc((sizeof(char)) * (nb_c_w(str, j, pattern) + 1));
        if (array[i] == NULL)
            return NULL;
        j += nb_spaces(str, j, pattern);
        for (k = 0; k != nb_c_w(str, j, pattern); k++)
            array[i][k] = str[j + k];
        array[i][k] = '\0';
        j += nb_c_w(str, j, pattern) + 1;
    }
    array[i] = 0;
    return array;
}
