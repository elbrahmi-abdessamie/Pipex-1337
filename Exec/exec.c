/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbrahm <aelbrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 09:35:20 by aelbrahm          #+#    #+#             */
/*   Updated: 2023/01/18 23:44:55 by aelbrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	execution(char **env, t_pipex *pipe_st)
{
	if (pipe_st->pid == 0)
	{
		dup2(pipe_st->fd[1], STDOUT_FILENO);
		close(pipe_st->fd[1]);
		close(pipe_st->fd[0]);
		if (execve(pipe_st->cmd_path, pipe_st->cmd_arg, env) == -1)
		{
			exev_err(strerror(errno), pipe_st);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		dup2(pipe_st->fd[0], STDIN_FILENO);
		close(pipe_st->fd[1]);
		close(pipe_st->fd[0]);
		waitpid(pipe_st->pid, NULL, 0);
	}
}

void	child(t_pipex *pipex, char **env, char *av)
{
	if (!pipex->ab_path)
		err(PAT);
	if (pipex->infile < 0 || pipex->outfile < 0)
		err(FD);
	if (pipe(pipex->fd) < 0)
		err(PERR);
	if (!*av)
		arg_err(KRED, pipex);
	pipex->pid = fork();
	if (pipex->pid < 0)
		err(strerror(errno));
	if (pipex->pid == 0)
	{
		pipex->cmd_arg = ft_split(av, ' ');
		pipex->cmd_path = cmd_path(pipex->ab_path, pipex->cmd_arg[0]);
		if (!pipex->cmd_path)
			cmd_path_err(pipex->cmd_arg[0]);
		execution(env, pipex);
	}
	else
		execution(env, pipex);
}

void	command(char *av, char **env, t_pipex *pipex)
{
	if (!*av)
		arg_err(KRED, pipex);
	pipex->cmd_arg = ft_split(av, ' ');
	pipex->cmd_path = cmd_path(pipex->ab_path, pipex->cmd_arg[0]);
	if (!pipex->cmd_path)
		cmd_path_err(pipex->cmd_arg[0]);
	if (execve(pipex->cmd_path, pipex->cmd_arg, env) == -1)
		exev_err(strerror(errno), pipex);
}
