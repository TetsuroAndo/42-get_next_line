/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 07:10:16 by teando            #+#    #+#             */
/*   Updated: 2024/11/04 15:35:37 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

/**
 * @brief バッファから改行文字を探し、必要に応じて新しい行を読み込む補助関数
 * @param buf 読み込みバッファ
 * @param fd 読み込み対象のファイルディスクリプタ
 * @return 1以上: 成功, 0: EOF到達, -1: エラー発生
 */
static int	read_buf(char *buf, int fd)
{
	int	size;

	size = read(fd, buf, BUFFER_SIZE);
	if (size <= 0)
		return (size);
	buf[size] = '\0';
	return (size);
}

/**
 * @brief 1行分のテキストを読み込んで処理する内部関数
 * @param r 読み込んだ行を格納する変数へのポインタ
 * @param newline 改行文字へのポインタを格納する変数へのポインタ
 * @param saved 前回の読み込みの残りを保持する静的バッファへのポインタ
 * @param fd 読み込み対象のファイルディスクリプタ
 * @return 0: 成功, -1: エラー
 */
static int	fetch_line(char **r, char **newline, t_fd_buf *fd_buf, int fd)
{
	char	buf[BUFFER_SIZE + 1];
	char	*tmp;
	int		code;

	while (!*newline)
	{
		code = read_buf(buf, fd);
		if (code <= 0)
			return (-1);
		tmp = ft_strjoin(*r, buf);
		if (!tmp)
			return (-1);
		free(*r);
		*r = tmp;
		*newline = ft_strchr(*r, '\n');
	}
	fd_buf->saved = ft_strdup(*newline + 1);
	if (!fd_buf->saved)
		return (-1);
	tmp = ft_strndup(*r, *newline - *r + 1);
	if (!tmp)
		return (-1);
	free(*r);
	*r = tmp;
	return (0);
}

static t_fd_buf	*search_fd_index(t_fd_buf *fd_bufs, int fd)
{
	int	i;

	i = 0;
	while (i++ < MAX_FD)
	{
		if (fd_bufs[i].fd == fd)
			return (&fd_bufs[i]);
		if (fd_bufs[i].fd == -1)
		{
			fd_bufs[i].fd = fd;
			fd_bufs[i].saved = NULL;
			return (&fd_bufs[i]);
		}
	}
	return (NULL);
}

/**
 * @brief ファイルから1行ずつテキストを読み込む関数
 * @param fd 読み込み対象のファイルディスクリプタ
 * @return 読み込んだ行の文字列（終端に改行文字を含む）
 *         エラーまたはEOFの場合はNULL
 */
char	*get_next_line(int fd)
{
	static t_fd_buf	fd_bufs[MAX_FD] = {{-1, NULL}};
	t_fd_buf		*current_buf;
	char			*newline;
	char			*r;
	int				code;

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE > 1000000)
		return (NULL);
	current_buf = search_fd_index(fd_bufs, fd);
	if (!current_buf)
		return (NULL);
	if (current_buf->saved)
		newline = ft_strchr(current_buf->saved, '\n');
	else
		newline = NULL;
	r = current_buf->saved;
	code = fetch_line(&r, &newline, current_buf, fd);
	if (code == -1 && current_buf->saved != r)
		free(current_buf->saved);
	if (code == -1 || (r && !*r))
	{
		free(r);
		r = NULL;
	}
	return (r);
}
