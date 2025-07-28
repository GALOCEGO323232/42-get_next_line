#include "get_next_line.h"

static char *extract_line(char **stash)
{
    char *nl;
    size_t len;
    char *line;
    size_t i;

    nl = gnl_strchr(*stash, '\n');
    if (nl)
        len = nl - *stash + 1;
    else
        len = gnl_strlen(*stash);
    line = (char *)malloc(len + 1);
    if (!line)
        return NULL;
    i = 0;
    while (i < len)
    {
        line[i] = (*stash)[i];
        i++;
    }
    line[len] = '\0';
    return line;
}

static void update_stash(char **stash)
{
    char *nl;
    char *new_stash;

    nl = gnl_strchr(*stash, '\n');
    if (!nl)
    {
        free(*stash);
        *stash = NULL;
        return;
    }
    new_stash = gnl_strdup(nl + 1);
    free(*stash);
    *stash = new_stash;
}

char *get_next_line(int fd)
{
    static char *stash;
    char buffer[BUFFER_SIZE + 1];
    ssize_t bytes;
    char *line;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return NULL;
    while (!gnl_strchr(stash, '\n'))
    {
        bytes = read(fd, buffer, BUFFER_SIZE);
        if (bytes < 0)
        {
            free(stash);
            stash = NULL;
            return NULL;
        }
        if(bytes == 0)
            break;
        buffer[bytes] = '\0';
        stash = gnl_strjoin(stash, buffer);
    }
    line = extract_line(&stash);
    update_stash(&stash);
    return line;
}
