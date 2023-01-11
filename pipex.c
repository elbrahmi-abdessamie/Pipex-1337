#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include "lb/libft.h"
#include "get_next_line/get_next_line.h"
#define KNRM  "\x1B[0m"
#define KRED  "\e[3m\x1B[31mCOMMAND NOT FOUND...\n"
#define RED    "\x1B[31m"
#define BLU     "\e[3m\e[1;34m"
typedef struct s_pipex
{
    int     fd[2];
    int     infile;
    int     outfile;
    int     pid;
    char    *cmd_path;
    char    **ab_path;
    char    **cmd_arg;
}   t_pipex;

int ft_strcmp(char *s1, char *s2)
{
    while ((unsigned char)*s1 == (unsigned char)*s2 && *s1)
    {
        s1++;
        s2++;
    }
    return ((unsigned char)*s1 - (unsigned char)*s2);
}

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
        // printf("[%s]\n",tmp_pth);
        tmp = ft_strjoin(slx, cmd);
        free(slx);
        if (access(tmp, F_OK) == 0)
            return(tmp);
        free(tmp);
        tmp_pth++;
    }
    return (NULL);
}
void    deallocat(t_pipex *pipe)
{
    int iter;

    iter = 0;
    while (pipe->ab_path[iter])
        free(pipe->ab_path[iter++]);
    free(pipe->ab_path);
}
void    execution(char **env, t_pipex *pipe_st)
{
    if (pipe_st->pid == 0)
    {
        dup2(pipe_st->fd[1], STDOUT_FILENO);
        close(pipe_st->fd[1]);
        close(pipe_st->fd[0]);
        if (execve(pipe_st->cmd_path, pipe_st->cmd_arg, env) == -1)
        {
            printf("%sError: %s\n",KRED, strerror(errno));
            exit(EXIT_FAILURE);
        }
    }else
    {
        dup2(pipe_st->fd[0], STDIN_FILENO);
        close(pipe_st->fd[1]);
        close(pipe_st->fd[0]);
        waitpid(pipe_st->pid, NULL, 0);
    }
}
void    child(t_pipex *pipex, char **env, char *av)
{
    if (pipe(pipex->fd) < 0)
    {
        printf("Error: %s\n",strerror(errno));
        exit(EXIT_FAILURE);
    }
    if (!*av)
    {
        ft_putstr_fd(KRED, 2);
        deallocat(pipex);
        exit(EXIT_FAILURE);    
    }
    pipex->pid = fork();
    if (pipex->pid < 0)
    {
        printf("Error: %s\n",strerror(errno));
        exit(EXIT_FAILURE);
    }
    if (pipex->pid == 0)
    {
        pipex->cmd_arg = ft_split(av, ' ');
        pipex->cmd_path = cmd_path(pipex->ab_path, pipex->cmd_arg[0]);
        if (!pipex->cmd_path)
        {
            printf("%s[%s]\t%s", BLU, pipex->cmd_arg[0],KRED);
            exit(EXIT_FAILURE);
        }
        execution(env, pipex);
    }
    else
        execution(env, pipex);
}
void command(char *av, char **env, t_pipex *pipex, int *sid)
{
    if (!*av)
    {
        ft_putstr_fd(KRED, 2);
        deallocat(pipex);
        exit(EXIT_FAILURE);    
    }
    pipex->cmd_arg = ft_split(av, ' ');
    pipex->cmd_path = cmd_path(pipex->ab_path, pipex->cmd_arg[0]);

    if (!pipex->cmd_path)
    {
        ft_putstr_fd(BLU, 2);
        write(2, "[", 1);
        ft_putstr_fd(pipex->cmd_arg[0], 2);
        write(2, "]\t", 2);
        ft_putstr_fd(KRED, 2);
        exit(EXIT_FAILURE);
    }
    if (execve(pipex->cmd_path, pipex->cmd_arg, env) == -1)
    {
        printf("%sError: %s\n",RED, strerror(errno));
        deallocat(pipex);
        exit(EXIT_FAILURE);
    }
}
void    here_doc(char *av, t_pipex *pipex, int *sid)
{
    int hr_doc = open(".heredoc.txt", O_CREAT | O_RDWR | O_TRUNC, 0644);
    pipex->infile = open("input", O_CREAT | O_RDWR | O_TRUNC, 0644);
    char *str_doc;
    *sid = 2;
    //  = (char *)malloc(sizeof(char) * 1000);
    dup2(pipex->infile, hr_doc);
        write(1, "pipe heredoc> ", 15);
        while (1)
        {
            str_doc = get_next_line(STDIN_FILENO);
            char *arg = ft_strjoin(av, "\n");
            if (ft_strcmp(str_doc, arg) == 0)
            {
                free(arg);
                break;
            }      
            ft_putstr_fd(str_doc, pipex->infile);
            free(str_doc);
        }
}
int main(int ac, char **av, char **env)
{
    t_pipex pipex;
    int     iter;

    char **p;
    iter = 1;
    if (ft_strcmp(av[1], "here_doc") == 0)
    {
        here_doc(av[2], &pipex, &iter);
        pipex.infile = open("input", O_CREAT | O_RDWR, 0664);
        dup2(pipex.infile, STDIN_FILENO);
    }        
    pipex.ab_path = get_path(env);
    if (iter == 1)
        pipex.infile = open(*(av + 1), O_CREAT | O_RDWR, 0664);
    pipex.outfile = open(*(av + ac - 1), O_CREAT | O_WRONLY, 0664);
    dup2(pipex.infile, STDIN_FILENO);
    while (++iter < ac - 2)
        child(&pipex, env, *(av + iter));
    dup2(pipex.outfile, STDOUT_FILENO);
    command(*(av + ac - 2), p, &pipex,&iter);
    // char **cmd_pth = ft_split("", ' ');
    // if (!(*cmd_pth))
    //     ft_putstr_fd(KRED, 2);
        // printf("%s%s\n",KRED, "COMMAND NOT FOUND...");
    // printf("%s\n",pipex.cmd_arg[0]);

}