/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbrahm <aelbrahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 18:44:12 by aelbrahm          #+#    #+#             */
/*   Updated: 2022/10/28 18:30:31 by aelbrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
