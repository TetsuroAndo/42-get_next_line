/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 07:10:16 by teando            #+#    #+#             */
/*   Updated: 2025/03/27 12:17:49 by teando           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "get_next_line.h"
#include <stdlib.h>
#include <string.h>

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	static char	*saved = NULL;
	char		*line;
	ssize_t		bytes_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!saved || !*saved)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read <= 0)
			return (NULL);
		buffer[bytes_read] = '\0';
		saved = buffer;
	}
	line = strtok(saved, "\n");
	if (line)
	{
		saved = strtok(NULL, "");
		return (strdup(line));
	}
	return (NULL);
}
