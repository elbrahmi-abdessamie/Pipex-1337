/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbrahm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 21:09:39 by aelbrahm          #+#    #+#             */
/*   Updated: 2022/11/25 21:13:32 by aelbrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *c)
{
	const char	*p;

	p = c;
	while (*p != '\0')
		p++;
	return (p - c);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	l;

	l = n;
	if (!dst && !src)
		return (NULL);
	if (dst == src)
		return (dst);
	while ((int)n-- > 0)
		*(char *)(dst++) = *(const char *)(src++);
	return (dst - l);
}

void	*ft_memchr(const void *str, int c, size_t n)
{
	unsigned char	*pstr;

	pstr = (unsigned char *)str;
	while (n--)
		if (*(pstr++) == (unsigned char)c)
			return (pstr - 0x1);
	return (NULL);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;
	char	*tmp;
	size_t	tt;

	tt = count * size;
	ptr = malloc(count * size);
	tmp = ptr;
	if (!ptr)
		return (NULL);
	while (tt--)
		*tmp++ = 0;
	return (ptr);
}

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	size_t	l;
	char	*sub;

	l = len;
	sub = (char *)malloc(len + 1 * sizeof(char));
	if (sub)
		while (*(s + start) && len--)
			*(sub + len) = *((s + len) + start);
	*(sub + l) = '\0';
	return (sub);
}
