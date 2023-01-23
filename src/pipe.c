#include "../includes/minishell.h"

/* if cmd is a builtin call the corresponding function
*/
int	exec_builtin_2(t_shell *minishell)
{
	if (!ft_strcmp("export", (minishell->cmd).name))
	{
		export_loop(minishell);
		return (1);
	}
	if (!ft_strcmp("unset", (minishell->cmd).name))
	{
		unset_loop(minishell);
		return (1);
	}
	if (!ft_strcmp("env", (minishell->cmd).name))
	{
		ft_env(minishell, 0);
		return (1);
	}
	return (0);
}

int	exec_builtin(t_shell *minishell)
{
	if ((minishell->cmd).name == NULL)
		return (1);
	if (!ft_strcmp("exit", (minishell->cmd).name))
	{
		ft_exit(minishell, EXEC);
		return (1);
	}
	if (!ft_strcmp("cd", (minishell->cmd).name))
	{
		ft_cd(minishell, get_env("PWD", minishell), ft_check_arg(minishell));
		return (1);
	}
	if (!ft_strcmp("echo", (minishell->cmd).name))
	{
		ft_echo(minishell);
		return (1);
	}
	if (!ft_strcmp("pwd", (minishell->cmd).name))
	{
		ft_pwd(minishell);
		return (1);
	}
	return (exec_builtin_2(minishell));
}

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