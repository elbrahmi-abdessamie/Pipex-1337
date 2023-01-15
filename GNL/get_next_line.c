/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbrahm <aelbrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 21:01:58 by aelbrahm          #+#    #+#             */
/*   Updated: 2023/01/14 14:27:37 by aelbrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "get_next_line.h"

char	*ft_strjoin_bst(const char *s1, const char *s2)
{
	size_t	s1len;
	size_t	s2len;
	size_t	tlen;
	char	*str;

	if (!s1)
		s1 = (char *)ft_calloc(1, sizeof(char));
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
	free((void *)s1);
	return (str);
}

static char	*read_file(int input_fd, char *res)
{
	char	*buffer;
	int		nread;

	buffer = (char *)ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer)
		return (NULL);
	nread = 1;
	while (nread > 0 && !ft_memchr(buffer, 0xA, nread))
	{
		nread = read(input_fd, buffer, BUFFER_SIZE);
		if (nread < 0)
		{
            if (res)
			    free(res);
			return (free(buffer), NULL);
		}
        if(nread == 0)
            break;
		buffer[nread] = 0;
		res = ft_strjoin_bst(res, buffer);
	}
	free(buffer);
	buffer = NULL;
	return (res);
}

static char	*r_line(char *buffer, int *ct_ln)
{
	char	*r_buffer;

	*ct_ln = 0;
    if (!buffer)
        return NULL;
	if (!*buffer)
		return (NULL);
	r_buffer = ft_memchr(buffer, 0xA, ft_strlen(buffer));
	if (r_buffer)
	{
		*ct_ln = r_buffer + 1 - buffer;
		return (ft_substr(buffer, 0, *ct_ln));
	}
	*ct_ln = ft_strlen(buffer);
	return (ft_substr(buffer, 0, *ct_ln));
}

static char	*nxt_ln(char *buffer, int *ct_ln)
{
	char	*bf_hld;
	size_t	len;

	if (!buffer)
		return (NULL);
	len = ft_strlen(buffer);
	if ((size_t)(*ct_ln) < ft_strlen(buffer))
	{
		bf_hld = ft_substr(buffer + *ct_ln, 0, len - *ct_ln);
		free(buffer);
		return (bf_hld);
	}
	return (free(buffer), NULL);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*output;
	int			count_ln;

	count_ln = 0;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = read_file(fd, buffer);
	if (!buffer)
		return (NULL);
	output = r_line(buffer, &count_ln);
	buffer = nxt_ln(buffer, &count_ln);
	return (output);
}
