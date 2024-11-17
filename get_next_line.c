/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 07:10:16 by teando            #+#    #+#             */
/*   Updated: 2024/11/17 20:27:09 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static ssize_t	read_buf_to_newline(char **r, char **newline, char **saved,
		int fd)
{
	ssize_t	read_total;
	ssize_t	size;
	char	*buf;

	read_total = 0;
	if (saved[fd])
		newline = ft_strchr(saved[fd], '\n');
	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (-1);
	while (!*newline)
	{
		size = read(fd, buf, BUFFER_SIZE);
		if (size <= 0)
			return (free(buf), size);
		buf[size] = '\0';
		read_total += size;
		*r = ft_realloc(*r, read_total + 1);
		if (!*r)
			return (free(buf), -1);
		ft_strlcat(*r, buf, read_total + 1);
		*newline = ft_strchr(*r + (read_total - size - 1), '\n');
	}
	return (free(buf), read_total);
}

static ssize_t	str_partitioning(char **r, char **newline, char **saved, int fd)
{
	*saved[fd] = ft_strdup(*newline + 1);
	if (!*saved[fd])
		return (free(*r), -1);
	(*r)[*newline - *r + 1] = '\0';
	return (1);
}

char	*get_next_line(int fd)
{
	static char	*saved[FD_MAX];
	char		*newline;
	char		*r;
	ssize_t		read_size;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	newline = NULL;
	r = saved[fd];
	if (!newline)
	{
		read_size = read_buf_to_newline(r, newline, saved[fd], fd);
		if (read_size == -1)
			return (free(r), NULL);
		if (read_size == 0)
			saved[fd] = NULL;
	}
	if (newline)
		if (str_partitioning(&r, &newline, &saved[fd], fd) == -1)
			return (free(r), NULL);
	return (r);
}
