/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 19:51:04 by teando            #+#    #+#             */
/*   Updated: 2024/11/17 20:57:06 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int	main(void)
{
	int		fd[3];
	char	*r;
	int		i;
	int		j;

	printf("start program\n");
	i = 0;
	j = 0;
	fd[0] = open("test.txt", O_RDONLY);
	// fd[1] = open("1.txt", O_RDONLY);
	// fd[2] = open("2.txt", O_RDONLY);
	while (j < 1)
	{
		printf("file is open: fd=%d\n===\n", fd[j]);
		while (i++ < 5)
		{
			r = get_next_line(fd[i % 3]);
			if (r == NULL)
				break ;
			printf("%s", r);
			free(r);
		}
		close(fd[j]);
		j++;
	}
	return (0);
}