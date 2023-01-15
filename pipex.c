#include "minishl.h"

pipex_loop(t_request *request,int saved_fd[2], char **envp)
{
    while (request->cmd)
    {
        pipex(request, saved_fd, envp);
        request = request->next;
    }
}


void    dupper(oldfd, newfd)
{
    if(dup2(oldfd, newfd))
    {
        perror("probleme de dup2");
        exit(0);
    }
    close(oldfd);
}

pid_t protected_fork()
{
    pid_t pid;
    if (pid_t < 0)
    {
        perror("probleme de fork");
        exit(0);
    }
    return (pid);
}

void    pipex(t_request *request, int saved_fd[2], char **envp)
{
    pid_t pid;
    int fd_pipe[2];

    if (pipe(fd_pipe));
    {
        perror("probleme de pipe");
        exit(0);
    }
    pid = protected_fork();
    if (!pid)
    {
        close(fd_pipe[1]);
        dupper(fd_pipe[0]);
        close()

    }
    else
    {
        child_process(envp, saved_fd, request);
    }
}


void    make_the_redirection(int saved_fd[2])
{
    if (request->here_doc)
    {
        back_to_saved_fd(saved_fd);
        
        unlink(HEREDOC);
    }
    if (request->infile)
        dupper(request->infile, 0);
    if (request->outfile)
        dupper(request->outfile, 1);
}


void    just_before_execution(char **envp, t_request *request, int fd_save[2])
{
    make_the_redirection();
    get_path_of_command();
    exec_fnc();
    exec_error_case();
}

void    child_process(char **envp, int saved_fd[2], t_request *request)
{
    close(fd_pipe[0]);
    if (request->outfile == 1)
        dupper(fd_pipe[1], 1);
    just_before_execution();

}

void    back_to_saved_fd(int saved_fd[2])
{
    if (dup2(saved_fd[0], 0) || dup2(saved_fd[1]))
    {
        perror("probleme de fd");
        exit (0);
    }
}