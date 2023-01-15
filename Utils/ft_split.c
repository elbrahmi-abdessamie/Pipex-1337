/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbrahm <aelbrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 22:14:17 by aelbrahm          #+#    #+#             */
/*   Updated: 2023/01/14 17:18:36 by aelbrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static size_t	ft_w_count(const char *s, char c);
static int		free_alloc(char **str, const char *s, size_t wc, char c);

char	**ft_split(const char *s, char c)
{
	size_t	w_c;
	char	**pstr;

	if (!s)
		return (NULL);
	w_c = ft_w_count(s, c);
	pstr = (char **)malloc((w_c + 1) * sizeof(char *));
	if (!pstr)
		return (NULL);
	*(pstr + w_c) = NULL;
	if (!(free_alloc(pstr, s, w_c, c)))
	{
		while (*pstr)
			free(*pstr++);
		free(pstr);
	}
	return (pstr);
}

static size_t	ft_w_count(const char *s, char c)
{
	size_t	count;

	count = 0;
	while (*s++)
		if (*(s - 1) != c && (!*s || *s == c))
			count++;
	return (count);
}

static int	free_alloc(char **str, const char *s, size_t wc, char c)
{
	int	tem_c;

	tem_c = 0;
	while (wc--)
	{
		while (*s == c && *s)
			s++;
		while (*(s + tem_c) != c && *(s + tem_c))
			tem_c++;
		if (tem_c)
			*str = ft_substr(s, 0, tem_c);
		if (!*str)
			return (0);
		str++;
		s = (s + tem_c);
		tem_c = 0;
	}
	return (1);
}
