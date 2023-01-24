/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niespana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 15:27:40 by niespana          #+#    #+#             */
/*   Updated: 2023/01/24 15:27:42 by niespana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishl.h"

char	*get_path(char *cmd)
{
	int		i;
	char	**paths;
	char	*cmd_path;
	char	*res;

	cmd_path = ft_strjoin("/", cmd);
	i = -1;
	paths = ft_split(getenv("PATH"), ':');
	res = ft_strjoin(paths[0], cmd_path);
	while (access(res, X_OK) && paths[++i])
	{
		free(res);
		res = ft_strjoin(paths[i], cmd_path);
	}
	free(cmd_path);
	i = -1;
	while (paths[++i])
		free(paths[i]);
	free(paths);
	return (res);
}

void	init_pipe(t_pipe *pipex, t_list *cmds)
{
	pipex->n = 0;
	pipex->len = ft_lstsize(cmds);
	while (pipex->n < pipex->len - 1)
	{
		if (pipe(pipex->fd[pipex->n++]))
			exit(1);
	}
	pipex->n = 0;
}

int exec_builtin(void (*f), char **params, t_shell *shell)
{
	f(params, shell);
	return (1);
}

int	is_builtin(char *cmd, char **params, t_shell *shell)
{
	if (!ft_strncmp(cmd, "echo", 5))
		return (exec_builtin(&ft_echo, params, shell));
	else if (!ft_strncmp(cmd, "cd", 3))
		return (exec_builtin(&ft_cd, params, shell));
	else if (!ft_strncmp(cmd, "pwd", 4))
		return (exec_builtin(&ft_pwd, params, shell));
	else if (!ft_strncmp(cmd, "env", 4))
		return (exec_builtin(&ft_env, params, shell));
	else if (!ft_strncmp(cmd, "unset", 6))
		return (exec_builtin(&ft_unset, params, shell));
	else if (!ft_strncmp(cmd, "export", 7))
		return (exec_builtin(&ft_export, params, shell));
	else if (!ft_strncmp(cmd, "exit", 5))
		return (exec_builtin(&ft_exit, params, shell));
	return (0)
}

void	exec_cmds(t_shell *shell, t_list *cmds)
{
	t_pipe	pipex;

	init_pipe(&pipex, cmds);
	while (cmds)
	{
		pipex.crt = (char **)cmds->content;
		pipex.cmd = get_path(pipex.crt[0]);
		pipex.pid = fork();
		if (pipex.pid == 0)
		{
			if (pipex.n < pipex.len - 1 && dup2(pipex.fd[pipex.n][1], shell->outfile) < 0)
				exit(1);
			if (pipex.n && dup2(pipex.fd[pipex.n - 1][0], shell->infile) < 0)
				exit(1);
			if (!is_builtin(pipex.crt[0], pipex.crt, shell))
				execve(pipex.cmd, pipex.crt, shell->env);
		}
		waitpid(pipex.pid, &pipex.status, 0);
		if (pipex.n < pipex.len - 1 && close(pipex.fd[pipex.n][1]))
			exit(1);
		if (pipex.n && close(pipex.fd[pipex.n - 1][0]))
			exit(1);
		cmds = cmds->next;
		pipex.n++;
		free(pipex.cmd);
	}
}
