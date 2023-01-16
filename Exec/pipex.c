/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbrahm <aelbrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 09:37:52 by aelbrahm          #+#    #+#             */
/*   Updated: 2023/01/16 21:42:57 by aelbrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int main(int ac, char **av, char **env)
{
    t_pipex pipex;
    int     iter;

    iter = 1;
    if (ac >= 5)
    {
        if (ft_strcmp(av[1], "here_doc") == 0)
        {
            if (ac <= 5)
                arg_check(HDC);
            here_doc(av[2], &pipex, &iter);
            pipex.infile = open("input", O_RDWR);
        }        
        pipex.ab_path = get_path(env);
        if (iter == 1)
            pipex.infile = open(*(av + 1), O_CREAT | O_RDWR, 0664);
        pipex.outfile = open(*(av + ac - 1), O_CREAT | O_WRONLY | O_TRUNC, 0664);
        dup2(pipex.infile, STDIN_FILENO);
        while (++iter < ac - 2)
            child(&pipex, env, *(av + iter));
        dup2(pipex.outfile, STDOUT_FILENO);
        command(*(av + ac - 2), env, &pipex);
    }
    err(MCMD);
}