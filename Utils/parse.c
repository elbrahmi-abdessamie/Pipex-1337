/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbrahm <aelbrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 09:30:52 by aelbrahm          #+#    #+#             */
/*   Updated: 2023/01/14 09:32:09 by aelbrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char    **get_path(char **env)
{
    while (*env)
    {
        if (ft_strncmp("PATH", *env, 4) == 0)
            return (ft_split(*env + 5, ':'));
        env++;
    }
    return (NULL);
}
char    *cmd_path(char **path, char *cmd)
{
    char    *slx;
    char    *tmp;
    char    **tmp_pth;

    tmp_pth = path;
    //add second condition to ensure that the provided argument is valid
    while (*tmp_pth && *cmd)
    {
        slx = ft_strjoin(*tmp_pth, "/");
        tmp = ft_strjoin(slx, cmd);
        free(slx);
        if (access(tmp, F_OK) == 0)
            return(tmp);
        free(tmp);
        tmp_pth++;
    }
    return (NULL);
}