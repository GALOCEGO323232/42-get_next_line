/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgagliar <kgagliar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 19:54:22 by kgagliar          #+#    #+#             */
/*   Updated: 2025/07/29 17:35:08 by kgagliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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

static void	ft_update_stash(char **stash)
{
	char	*nl;
	char	*new_stash;

	nl = ft_gnl_strchr(*stash, '\n');
	if (!nl)
	{
		free(*stash);
		*stash = NULL;
		return ;
	}
	new_stash = ft_gnl_strdup(nl + 1);
	free(*stash);
	*stash = new_stash;
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (ft_read_stash(fd, &stash) == -1)
	{
		free(stash);
		stash = NULL;
		return (NULL);
	}
	line = ft_line_extract(&stash);
	if (!line || line[0] == '\0')
	{
		free(line);
		free(stash);
		stash = NULL;
		return (NULL);
	}
	ft_update_stash(&stash);
	return (line);
}
