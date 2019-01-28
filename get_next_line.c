/*
** EPITECH PROJECT, 2018
** get next line
** File description:
** description
*/

#include "get_next_line.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <zconf.h>

int my_strlen(char *str)
{
    int i = 0;

    if (str == NULL)
        return (i);
    while (str[i] != '\0')
        i++;
    return (i);
}

char *update_line(char *buffer, char *line)
{
    int i = 0;
    int j = 0;
    int prev_size = my_strlen(line);
    int buffer_size = my_strlen(buffer);
    char *updated = malloc(sizeof(char) * (prev_size + buffer_size + 1));

    if (updated == NULL)
        return (NULL);

    if (line != NULL) {
        for (; line[i] != '\0'; i++) {
            updated[i] = line[i];
        }
    }
    if (buffer != NULL) {
        for (; buffer[j] != '\0'; i++, j++) {
            updated[i] = buffer[j];
        }
    }
    updated[prev_size + buffer_size] = '\0';
    return (updated);
}

int previous_line_char(char *line)
{
    if (line == NULL)
        return (0);
    for (int i = 0; line[i] != '\0'; i++) {
        if (line[i] == '\n')
            return (1);
    }
    return (0);
}

char *my_strndup(char *line, int sup_char)
{
    int i = 0;
    char *str = malloc(sizeof(char) * (sup_char + 1));

    if (str == NULL)
        return (NULL);
    while (line[i] != '\0' && i < sup_char) {
        str[i] = line[i];
        i++;
    }
    str[sup_char] = '\0';
    return (str);
}

char *get_next_line(int fd)
{
    int i = 0;
    static char *str = NULL;
    char *line = NULL;
    char *buffer = malloc(sizeof(char) * (READ_SIZE + 1));
    int my_read;

    if (buffer == NULL || fd == -1)
        return (NULL);
    line = update_line(str, line);
    for (; previous_line_char(line) != 1; line = update_line(buffer, line)) {
        my_read = read(fd, buffer, READ_SIZE);
        if (my_read == -1 || buffer[0] == '\0')
            return (NULL);
        if (my_read == 0)
            return (line);
        buffer[READ_SIZE] = '\0';
    }
    for (; line[i] != '\0' && line[i] != '\n'; i++);
    str = my_strndup(line + i + 1, my_strlen(line + i + 1));
    line = my_strndup(line, i);
    return (line);
}