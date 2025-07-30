/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgagliar <kgagliar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 19:54:22 by kgagliar          #+#    #+#             */
/*   Updated: 2025/07/30 20:01:39 by kgagliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static int	ft_free_buffer(char *buffer)
{
	if (buffer)
		free(buffer);
	return (-1);
}

static int	ft_read_stash(int fd, char **stash)
{
	char	*buffer;
	ssize_t	bytes;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (-1);
	while (*stash == NULL || !ft_gnl_strchr(*stash, '\n'))
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes < 0)
			return (ft_free_buffer(buffer));
		if (bytes == 0)
			break ;
		buffer[bytes] = '\0';
		*stash = ft_gnl_strjoin(*stash, buffer);
		if (!*stash)
			return (ft_free_buffer(buffer));
	}
	free(buffer);
	if (*stash == NULL)
		*stash = ft_gnl_strdup("");
	return (0);
}

static char	*ft_line_extract(char **stash)
{
	char	*nl;
	size_t	len;
	char	*line;
	size_t	i;

	if (!*stash || (*stash)[0] == '\0')
		return (NULL);
	nl = ft_gnl_strchr(*stash, '\n');
	if (nl)
		len = nl - *stash + 1;
	else
		len = ft_gnl_strlen(*stash);
	line = (char *)malloc(len + 1);
	if (!line)
		return (NULL);
	i = 0;
	while (i < len)
	{
		line[i] = (*stash)[i];
		i++;
	}
	line[len] = '\0';
	return (line);
}

static void	ft_stash(char **stash)
{
	char	*nl;
	char	*new_stash;

	if (!stash || !*stash)
		return ;
	nl = ft_gnl_strchr(*stash, '\n');
	if (!nl)
	{
		free(*stash);
		*stash = NULL;
		return ;
	}
	new_stash = ft_gnl_strdup(nl + 1);
	if (!new_stash)
	{
		free(*stash);
		*stash = NULL;
		return ;
	}
	free(*stash);
	*stash = new_stash;
}

char	*get_next_line(int fd)
{
	static char	*stash[STASH_MAX];
	char		*line;

	if (fd < 0 || fd >= STASH_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	if (ft_read_stash(fd, &stash[fd]) == -1)
	{
		free(stash[fd]);
		stash[fd] = NULL;
		return (NULL);
	}
	line = ft_line_extract(&stash[fd]);
	if (!line)
	{
		free(stash[fd]);
		stash[fd] = NULL;
		return (NULL);
	}
	ft_stash(&stash[fd]);
	return (line);
}
