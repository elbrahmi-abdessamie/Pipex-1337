/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbrahm <aelbrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 11:02:46 by aelbrahm          #+#    #+#             */
/*   Updated: 2023/01/14 17:14:11 by aelbrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void    deallocat(t_pipex *pipe)
{
    int iter;

    iter = 0;
    while (pipe->ab_path[iter])
        free(pipe->ab_path[iter++]);
    free(pipe->ab_path);
}

void    cmd_path_err(char *cmd)
{
    ft_putstr_fd(BLU, 2);
    write(2, "[", 1);
    ft_putstr_fd(cmd, 2);
    write(2, "]\t", 2);
    ft_putstr_fd(KRED, 2);
    exit(EXIT_FAILURE);
}
void    exev_err(char *err, t_pipex *pipex)
{
    printf("%sError: %s\n",RED, err);
    deallocat(pipex);
    exit(EXIT_FAILURE);
}

void    arg_err(char *str, t_pipex *pipex)
{
    ft_putstr_fd(str, 2);
    deallocat(pipex);
    exit(EXIT_FAILURE);
}

void    err(char *str)
{
    ft_putstr_fd(str, 2);
    exit(EXIT_FAILURE);
}