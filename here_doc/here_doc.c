/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbrahm <aelbrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 09:23:28 by aelbrahm          #+#    #+#             */
/*   Updated: 2023/01/19 00:06:37 by aelbrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_strcmp(char *s1, char *s2)
{
	while ((unsigned char)*s1 == (unsigned char)*s2 && *s1)
	{
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

void	compare(char *str_doc, char *arg, t_pipex *pipex)
{
	ft_putstr_fd(str_doc, pipex->infile);
	free(str_doc);
	free(arg);
}

void	here_doc(char *av, t_pipex *pipex, int *sid)
{
	char	*str_doc;
	char	*arg;
	int		hr_doc;

	hr_doc = open(".heredoc", O_CREAT | O_RDWR, 0644);
	pipex->infile = open("input", O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (hr_doc < 0 || pipex->infile < 0)
		err(FD);
	*sid = 2;
	dup2(pipex->infile, hr_doc);
	while (1)
	{
		write(1, "pipe heredoc> ", 15);
		str_doc = get_next_line(STDIN_FILENO);
		if (!str_doc)
			break ;
		arg = ft_strjoin(av, "\n");
		if (ft_strcmp(str_doc, arg) == 0 || ft_strcmp(str_doc, "EOF\n") == 0)
		{
			free(arg);
			break ;
		}
		compare(str_doc, arg, pipex);
	}
	unlink(".heredoc");
}
