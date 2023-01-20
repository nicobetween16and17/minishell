#include "../includes/minishell.h"
/* fork the process
 * return the pid on the parent side
 * on the child side
 * call ft_redirect to handle redirection of io
 * and openig/creation of files
 * the fork terminate normaly after that if no cmd nor buitin
 * call buitin if element tokenized to COMMAND is a builtin
 * call execve if cmd exist and builtin wasn't called
 */
pid_t	exec_cmd(t_shell *minishell)
{
	int		proc_pid;
	t_cmd	*cmd;

	proc_pid = fork();
	if (proc_pid > 0)
		return (proc_pid);
	else if (proc_pid < 0)
		ft_exit(minishell, FAILED_FORK);
	cmd = &minishell->cmd;
	if (ft_redirect(minishell) == 0)
		ft_exit(minishell, NULL);
	if (cmd->name == NULL)
		ft_exit(minishell, NULL);
	if (exec_builtin(minishell))
		ft_exit(minishell, NULL);
	else if (cmd->path)
	{
		execve(cmd->path, cmd->arg, cmd->envp);
		ft_exit(minishell, FAILED_EXEC);
	}
	ft_exit(minishell, NULL);
	return (-1);
}

/* set up the pipes and execute the command
 * and perform the neccessary close()
 * each iteration of the loop will creat a pipe except the last
 * each iteration of the loop will set the fd_in to the read end
 * of the pipe except the first
 * each iteration of the loop will set the fd_out to the write end
 * of the pipe except the last
 */
void	exec_pipeline(t_shell *minishell)
{
	int	i;
	int	fd[2];

	i = 0;
	while (i <= minishell->nbr_pipe)
	{
		ft_build_cmd(minishell);
		if (i > 0)
			(minishell->cmd).fd_in = fd[0];
		if (i < minishell->nbr_pipe)
		{
			if (pipe((fd)) == -1)
				ft_exit(minishell, FAILED_PIPE);
			(minishell->cmd).fd_out = fd[1];
		}
		(minishell->pid)[i] = exec_cmd(minishell);
		if (i < minishell->nbr_pipe)
			close(fd[1]);
		if (i > 0)
			close((minishell->cmd).fd_in);
		move_pipeline(minishell);
		reset_cmd(minishell);
		i++;
	}
}