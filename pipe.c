#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include "lb/libft.h"
// #include <errno.h>
#define MAX(a,b) ((a > b) ? a : b)
#define MIN(a,b) ((a < b) ? a : b)
typedef struct s_pipe{
    int     pid1;
    int     pid2;
    int     fd[2];
    int     infile;
    int     outfile;
    char    *cmd_path;
    char    **cmd_args;
    char    **path;
} t_pipe;
char    **ft_get_path(char **envp)
{
    while (ft_strncmp("PATH", *envp, 4))
        envp++;
    return (ft_split(*envp + 5, ':'));
}
char    *ft_check_path(t_pipe *pipe)
{
    char    **path;
    char    **tmp;
    char    *thld;
    char    *slxd;
    int     i;

    i = 0;
    path = pipe->path;
    tmp = path;
    while (*path)
    {
        thld = ft_strjoin(*path, "/");
        slxd = ft_strjoin(thld, pipe->cmd_args[0]);
        free(thld);
        if (access(slxd, F_OK) == 0)
            return slxd;
        free(slxd);
        path++;
    }
    return NULL;
}
void    dealloc_child(t_pipe *pipe)
{
    int i;

    i = 0;
    while (pipe->cmd_args[i])
    {
        free(pipe->cmd_args[i]);
        i++;
    }
    free(pipe->cmd_args);
    free(pipe->cmd_path);
}
void    dealloc_parent(t_pipe *pipe)
{
    int i;

    i = 0;
    close(pipe->fd[0]);
    close(pipe->fd[1]);
    while (pipe->path[i])
    {
        free(pipe->path[i]);
        i++;
    }
    free(pipe->path);
}

void    child(char *av, char **envp, t_pipe *pipex)
{
    if (pipe(pipex->fd) < 0)
        exit(1);
    pipex->pid1 = fork();
    if (pipex->pid1 == 0)
    {

        pipex->cmd_args = ft_split(av, ' ');
  
        pipex->cmd_path = ft_check_path(pipex);
        if (!pipex->cmd_path)
        {
            printf("CMD not found ");
            dealloc_child(pipex);
            exit(1);
        }
        dup2(pipex->fd[1], STDOUT_FILENO);
        close(pipex->fd[0]);
        close(pipex->fd[1]);
        execve(pipex->cmd_path, pipex->cmd_args, envp);
    }
    else
    {
        dup2(pipex->fd[0], STDIN_FILENO);
        close(pipex->fd[0]);
        close(pipex->fd[1]);
        waitpid(pipex->pid1, NULL, 0);
    }
}
void command(char *av, char **env, t_pipe *pipex)
{
    pipex->cmd_args = ft_split(av, ' ');
    pipex->cmd_path = ft_check_path(pipex);
    pipex->outfile = open("out", O_CREAT | O_WRONLY, 0664);
    dup2(pipex->outfile, STDOUT_FILENO);
    execve(pipex->cmd_path, pipex->cmd_args, env);
}
// void    ft_sec_child(char **av, char **envp, t_pipe pipe)
// {
//     pipe.cmd_args = ft_split(*(av + 3), ' ');
//     pipe.outfile = open(*(av + 4), O_CREAT | O_WRONLY, 0664);
//     pipe.cmd_path = ft_check_path(&pipe);
//     if (!pipe.cmd_path)
//     {
//         printf("CMD not found2\n");
//         dealloc_child(&pipe);
//         exit(1);
//     }
//     dup2(pipe.fd[0], STDIN_FILENO);
//     dup2(pipe.outfile, STDOUT_FILENO);
//     close(pipe.fd[0]);
//     close(pipe.fd[1]);
//     execve(pipe.cmd_path, pipe.cmd_args, envp);
// }
int main(int argc, char **argv, char **envp)
{
    unlink(*(argv + argc - 1));
    t_pipe pipex;
    pipex.path = ft_get_path(envp);
    pipex.infile = open(*(argv + 1), O_CREAT | O_RDONLY, 0664);
    pipex.outfile = open(*(argv + argc - 1), O_CREAT | O_RDONLY, 0664);
    dup2(pipex.infile, STDIN_FILENO);
    int i = 1;
    while (++i < argc - 2)
        child(*(argv + i), envp, &pipex);
    dup2(pipex.outfile, STDOUT_FILENO);
    command(*(argv + argc - 2), envp, &pipex);
    return 0;
    // if (pipe(pipex.fd) == -1)
    //     return 1;
    // pipex.pid1 = fork();
    // if (pipex.pid1 < 0)
    //     return 2;
    // if (pipex.pid1 == 0)
    //     ft_fst_child(argv, envp, &pipex);
    // pipex.pid2 = fork();
    // if (pipex.pid2 < 0)
    //     return 3;
    // if (pipex.pid2 == 0)
    //     ft_sec_child(argv, envp, pipex);
    // close(pipex.fd[0]);
    // close(pipex.fd[1]);
    // waitpid(pipex.pid1, NULL, 0);
    // waitpid(pipex.pid2, NULL, 0);
    // dealloc_parent(&pipex);
    //     setbuf(stdout, NULL); //disable buffring of stdout
    return 0;
}