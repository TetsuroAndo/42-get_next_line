/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 19:51:04 by teando            #+#    #+#             */
/*   Updated: 2024/11/06 11:21:44 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int	main(void)
{
	int		fd;
	char	*r;
	int		i;

	i = 0;
	printf("start program\n");
	fd = open("test.txt", O_RDONLY);
	if (fd == -1)
	{
		perror("Error: I can't open file\n");
		return (1);
	}
	printf("file is open: fd=%d\n", fd);
	printf("BUFFER_SIZE: %d\n===\n", BUFFER_SIZE);
	while (i++ < 4)
	{
		r = get_next_line(fd);
		if (r == NULL)
			break ;
		printf("%s", r);
		free(r);
	}
	close(fd);
	return (0);
}
