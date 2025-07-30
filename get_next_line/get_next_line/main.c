/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgagliar <kgagliar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 18:30:30 by kgagliar          #+#    #+#             */
/*   Updated: 2025/07/30 18:58:25 by kgagliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h> 

int	main(void)
{
	int	fd;
	char *line;

	fd = open("test.txt", O_RDONLY);
	if (fd < 0)
	{
		write(1, "ERROR", 5);
		return (0);
	}
	while ((line = get_next_line(fd)) != NULL)
	{
		write(1, line, ft_gnl_strlen(line));
		free(line);
	}
	close(fd);
}