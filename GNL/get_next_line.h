#ifndef GET_NEXT_LINE_H
#define GET_NEXT_LINE_H

#include <stdlib.h>
#include <unistd.h>

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 42
#endif

char *get_next_line(int fd);
char *gnl_strchr(const char *s, int c);
char *gnl_strdup(const char *s);
char *gnl_strjoin(char *s1, char *s2);
size_t gnl_strlen(const char *s);

#endif