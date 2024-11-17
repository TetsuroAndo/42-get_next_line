/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 09:01:59 by teando            #+#    #+#             */
/*   Updated: 2024/11/18 07:52:19 by teando           ###   ########.fr       */
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

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*r;
	char	*r_head;
	size_t	size;

	if (!s1)
		s1 = "";
	if (!s2)
		s2 = "";
	size = ft_strlen(s1) + ft_strlen(s2) + 1;
	r_head = (char *)malloc(sizeof(char) * size);
	if (r_head)
	{
		r = r_head;
		while (*s1)
			*r++ = *s1++;
		while (*s2)
			*r++ = *s2++;
		*r = '\0';
	}
	return (r_head);
}

// size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
// {
// 	size_t	dst_len;
// 	size_t	src_len;

// 	if (!dstsize || !dst)
// 		return (ft_strlen(src));
// 	dst_len = ft_strlen(dst);
// 	if (dstsize <= dst_len)
// 		dst_len = dstsize;
// 	src_len = ft_strlen(src);
// 	if (dstsize > dst_len)
// 	{
// 		dst += dst_len;
// 		while (*src && dst_len < dstsize - 1)
// 			*dst++ = (dstsize--, *src++);
// 		*dst = '\0';
// 	}
// 	return (dst_len + src_len);
// }

// void	*ft_realloc(void *ptr, size_t size)
// {
// 	void	*newptr;
// 	size_t	oldsize;
	
// 	if (!ptr)
// 		return (malloc(1 * size));
// 	if(!size)
// 		return (free(ptr), NULL);
// 	newptr = malloc(1 * size);
// 	if (!newptr)
// 		return (NULL);
// 	oldsize = ft_strlen(ptr);
// 	if (oldsize < size)
// 		ft_strlcat(newptr, ptr, oldsize + 1);
// 	else
// 		ft_strlcat(newptr, ptr, size);
// 	free(ptr);
// 	return (newptr);
// }
	// while (++i < old_size)
		// 	((unsigned char *)new_ptr)[i] = ((unsigned char *)ptr)[i];