/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 09:01:59 by teando            #+#    #+#             */
/*   Updated: 2024/11/18 01:56:16 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (*s++)
		len++;
	return (len);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (!(char)c)
		return ((char *)s);
	return (NULL);
}

char	*ft_strdup(const char *s)
{
	char	*r;
	char	*r_head;
	size_t	len;

	len = ft_strlen(s);
	r_head = (char *)malloc(sizeof(char) * (len + 1));
	if (r_head)
	{
		r = r_head;
		while (len--)
			*r++ = *s++;
		*r = '\0';
	}
	return (r_head);
}

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dst_len;
	size_t	src_len;

	if (dstsize == 0)
		return (ft_strlen(src));
	dst_len = ft_strlen(dst);
	if (dstsize <= dst_len)
		dst_len = dstsize;
	src_len = ft_strlen(src);
	if (dstsize > dst_len)
	{
		dst += dst_len;
		while (*src && dst_len < dstsize - 1)
			*dst++ = (dstsize--, *src++);
		*dst = '\0';
	}
	return (dst_len + src_len);
}


void	*ft_realloc(void *ptr, size_t size)
{
	void	*new_ptr;
	size_t	old_size;
	ssize_t	i;

	
	if (!ptr)
		return (malloc(1 * size));
	if(!size)
		return (NULL);
	new_ptr = malloc(1 * size);
	if (!new_ptr)
		return (NULL);
	old_size = ft_strlen(ptr);
	i = -1;
	if (old_size < size)
		while (++i < old_size)
			((unsigned char *)new_ptr)[i] = ((unsigned char *)ptr)[i];
	else
		while (++i < size)
			((unsigned char *)new_ptr)[i] = ((unsigned char *)ptr)[i];
	free(ptr);
	return (new_ptr);
}
