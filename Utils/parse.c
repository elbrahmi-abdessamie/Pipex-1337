/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbrahm <aelbrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 09:30:52 by aelbrahm          #+#    #+#             */
/*   Updated: 2023/01/17 21:15:02 by aelbrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**get_path(char **env)
{
	while (*env)
	{
		if (ft_strncmp("PATH", *env, 4) == 0)
			return (ft_split(*env + 5, ':'));
		env++;
	}
	return (NULL);
}

int	cmd_check(char *cmd)
{
	int	count;

	count = 0;
	while (*cmd)
	{
		if (*cmd == 0x2f || *cmd == 0x2e)
			count++;
		else if (*cmd != 0x2f && *cmd != 0x2e)
			break ;
		cmd++;
	}
	return (count);
}

char	*cmd_path(char **path, char *cmd)
{
	char	*slx;
	char	*tmp;
	char	**tmp_pth;

	tmp_pth = path;
	if (access(cmd, X_OK | F_OK) == 0)
		return (cmd);
	if (cmd_check(cmd) == 1)
		err(DIR2);
	if (cmd_check(cmd) >= 2)
		err(DIR1);
	while (*tmp_pth && *cmd)
	{
		slx = ft_strjoin(*tmp_pth, "/");
		tmp = ft_strjoin(slx, cmd);
		free(slx);
		if (access(tmp, F_OK) == 0)
			return (tmp);
		free(tmp);
		tmp_pth++;
	}
	return (NULL);
}
