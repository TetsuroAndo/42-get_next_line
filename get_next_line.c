/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 07:10:16 by teando            #+#    #+#             */
/*   Updated: 2024/11/06 04:55:07 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/**
 * @brief バッファ分の文字列を読み込む補助関数
 * @param buf 読み込みバッファ
 * @param fd 読み込み対象のファイルディスクリプタ
 * @return 1以上: 成功, 0: EOF到達, -1: エラー発生
 */
static ssize_t	read_buf(char **buf, int fd)
{
	ssize_t	size;

	*buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!*buf)
		return (-1);
	size = read(fd, *buf, BUFFER_SIZE);
	if (size <= 0)
	{
		free(*buf);
		*buf = NULL;
		return (size);
	}
	(*buf)[size] = '\0';
	return (size);
}

/**
 * @brief 1行分のテキストを読み込んで処理する内部関数
 * @param r 読み込んだ行を格納する変数へのポインタ
 * @param newline 改行文字へのポインタを格納する変数へのポインタ
 * @param saved 前回の読み込みの残りを保持する静的バッファへのポインタ
 * @param fd 読み込み対象のファイルディスクリプタ
 * @return 1以上: 成功, 0: EOF到達, -1: エラー発生
 */
static ssize_t	fetch_one_line(char **r, char **newline, char **saved, int fd)
{
	char	*buf;
	char	*tmp;
	ssize_t	code;

	while (!*newline)
	{
		code = read_buf(&buf, fd);
		if (code <= 0)
			return (code);
		tmp = ft_strjoin(*r, buf);
		free(buf);
		if (!tmp)
			return (-1);
		free(*r);
		*r = tmp;
		*newline = ft_strchr(*r, '\n');
	}
	*saved = ft_strdup(*newline + 1);
	if (!*saved)
		return (-1);
	tmp = endfree_strndup(*r, *newline - *r + 1);
	if (!tmp)
		return (-1);
	*r = tmp;
	return (1);
}

/**
 * @brief ファイルから1行ずつテキストを読み込む関数
 * @param fd 読み込み対象のファイルディスクリプタ
 * @return 読み込んだ行の文字列（終端に改行文字を含む）
 *         エラーまたはEOFの場合はNULL
 */
char	*get_next_line(int fd)
{
	static char	*saved;
	char		*newline;
	char		*r;
	ssize_t		code;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (saved)
		newline = ft_strchr(saved, '\n');
	else
		newline = NULL;
	r = saved;
	code = fetch_one_line(&r, &newline, &saved, fd);
	if (code <= 0 && r && *r)
	{
		if (code == -1 && saved != r)
			free(saved);
		saved = NULL;
	}
	if (code == -1 || (r && !*r))
	{
		free(r);
		r = NULL;
	}
	return (r);
}
