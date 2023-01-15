/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbrahm <aelbrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 16:51:08 by aelbrahm          #+#    #+#             */
/*   Updated: 2023/01/14 17:40:12 by aelbrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	if (!n)
		return (n);
	while (((unsigned char)*s1 == (unsigned char)*s2) && --n > 0 && *s1)
	{
		s1++;
		s2++;
	}
	return ((unsigned char)(*s1) - (unsigned char)*s2);
}

char	*ft_strdup(const char *src)
{
	size_t	ln;
	char	*dst;
	char	*s;

	s = (char *)src;
	ln = ft_strlen(src);
	dst = (char *)malloc(ln + 1);
	if (!dst)
		return (NULL);
	while (*s)
		*(dst++) = *(s++);
	*(dst) = '\0';
	return (dst - (ln));
}

void	ft_putstr_fd(char *s, int fd)
{
	write(fd, s, ft_strlen(s));
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	size_t	s1len;
	size_t	s2len;
	size_t	tlen;
	char	*str;

	if (!s1 || !s2)
		return (NULL);
	s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	tlen = s1len + s2len;
	str = (char *)malloc((tlen + 1) * sizeof(char));
	if (!str)
		return (NULL);
	ft_memcpy(str, s1, s1len);
	ft_memcpy((str + s1len), s2, s2len);
	*(str + tlen) = '\0';
	return (str);
}