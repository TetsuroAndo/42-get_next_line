/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 19:51:04 by teando            #+#    #+#             */
/*   Updated: 2025/03/27 12:42:46 by teando           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int	main(void)
{
	int		fd;
	char	*r;
	int		i;

	i = -1;
	fd = open("test.txt", O_RDONLY);
	printf("file is open: fd=%d\n===\n", fd);
	while (++i < 20)
	{
		r = get_next_line(fd);
		// if (!r)
		// 	break;
		fprintf(stdout, "%s\n", r);
		free(r);
	}
	close(fd);
	return (0);
}
