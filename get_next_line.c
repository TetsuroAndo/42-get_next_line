/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 07:10:16 by teando            #+#    #+#             */
/*   Updated: 2024/11/18 08:44:15 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>

static ssize_t	read_buf_to_newline(char **r, char **newline, int fd)
{
	ssize_t read_total;
	ssize_t	size;
	char	*temp;
	char	*buf;

	read_total = 0;
	if (*r)
		*newline = ft_strchr(*r, '\n');
	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (-1);
	while (!*newline)
	{
		size = read(fd, buf, BUFFER_SIZE);
		if (size <= 0)
			return (free(buf), size);
		buf[size] = '\0';
		read_total += size;
		temp = ft_strjoin(*r, buf);
		free(*r);
		if (!temp)
			return (free(buf), -1);
		*r = temp;
		*newline = ft_strchr(*r + (read_total - size), '\n');
	}
	return (free(buf), read_total);
}

char	*get_next_line(int fd)
{
	static char	*saved[FD_MAX];
	char		*newline;
	char		*temp;
	char		*r;
	ssize_t		read_size;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= FD_MAX)
		return (NULL);
	r = saved[fd];
	newline = NULL;
	read_size = read_buf_to_newline(&r, &newline, fd);
	if (read_size == -1)
		return (free(r), free(saved[fd]), NULL);
	if (read_size == 0)
		saved[fd] = NULL;
	if (newline)
	{
		temp = ft_strdup(newline + 1);
		if (!temp)
			return (free(r), NULL);
		saved[fd] = temp;
		r[newline - r + 1] = '\0';
	}
	return (r);
}

// if (code <= 0 && r && *r)
// {
// 	if (code == -1 && saved != r)
// 		free(saved);
// 	saved = NULL;
// }
// if (code == -1 || (r && !*r))
// {
// 	free(r);
// 	r = NULL;
// }
