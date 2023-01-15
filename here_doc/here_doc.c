/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbrahm <aelbrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 09:23:28 by aelbrahm          #+#    #+#             */
/*   Updated: 2023/01/15 14:47:46 by aelbrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int ft_strcmp(char *s1, char *s2)
{
    while ((unsigned char)*s1 == (unsigned char)*s2 && *s1)
    {
        s1++;
        s2++;
    }
    return ((unsigned char)*s1 - (unsigned char)*s2);
}

void    arg_check(char *str)
{
    ft_putstr_fd(str, 2);
    exit(EXIT_FAILURE);
}
void    here_doc(char *av, t_pipex *pipex, int *sid)
{
    char    *str_doc;
    char    *arg;
    int     hr_doc;

    hr_doc = open(".heredoc", O_CREAT | O_RDWR, 0644);
    pipex->infile = open("input", O_CREAT | O_RDWR | O_TRUNC, 0644);
    *sid = 2;
    dup2(pipex->infile, hr_doc);
    write(1, "pipe heredoc> ", 15);
    while (1)
    {
        str_doc = get_next_line(STDIN_FILENO);
        arg = ft_strjoin(av, "\n");
        if (ft_strcmp(str_doc, arg) == 0 || ft_strcmp(str_doc, "EOF\n") == 0)
        {
            free(arg);
            break;
        }      
        ft_putstr_fd(str_doc, pipex->infile);
        free(str_doc);
    }
    unlink(".heredoc");
}