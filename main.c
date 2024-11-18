/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 19:51:04 by teando            #+#    #+#             */
/*   Updated: 2024/11/18 11:10:51 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
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
	i = -1;
	j = 0;
	fd[0] = open("test.txt", O_RDONLY);
	fd[1] = open("1.txt", O_RDONLY);
	fd[2] = open("2.txt", O_RDONLY);
	// fd[0] = 0;
	while (j < 1)
	{
		printf("file is open: fd=%d\n===\n", fd[j]);
		while (++i < 50)
		{
			printf("i = %d\n", i);
			r = get_next_line(fd[i % 3]);
			printf("%s", r);
			// if (r == NULL)
			// 	break ;
			free(r);
		}
		close(fd[j]);
		j++;
	}
	return (0);
}
