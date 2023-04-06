/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katalbi <katalbi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 15:27:40 by niespana          #+#    #+#             */
/*   Updated: 2023/04/04 11:40:38 by katalbi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishl.h"

/*
 * search for a valid path for the command and returns it
 */
char	*get_path(char *cmd, char *path)
{
	int		i;
	char	**paths;
	char	*cmd_path;
	char	*res;

	if (!path)
		return (0);
	cmd_path = ft_strjoin("/", cmd);
	i = -1;
	paths = ft_split(path, ':');
	res = ft_strjoin(paths[0], cmd_path);
	while (access(res, X_OK) && paths[++i])
	{
		free(res);
		res = ft_strjoin(paths[i], cmd_path);
	}
	if (access(res, X_OK))
		res = safe_free(res);
	free(cmd_path);
	i = -1;
	while (paths[++i])
		free(paths[i]);
	free(paths);
	return (res);
}

/*
 * create a pipe between the exit of the last pipe and the entry of the new pipe
 * then if it is a builtin, executes it and exits, else execute it with 'execve'
 * close each ends of the pipe before and after the execution
 */
void	pipe_exec2(t_shell *shell, t_pipe *pipex)
{
	printf("infile %d outfile %d pipex->len %d\n", shell->infile, shell->outfile, pipex->len);
	if (pipex->pid[pipex->nb_pid] == 0)
	{
		if (pipex->n < pipex->len && printf("duping [%d][1] with %d\n", pipex->n, shell->outfile) &&\
		dup2(pipex->fd[pipex->n][1], shell->outfile) < 0 && print_err(1, "failed\n"))
			exit(1);
		if (pipex->n < pipex->len && print_err(3,"closing [", ft_itoa(pipex->n), "][1]\n") &&close(pipex->fd[pipex->n][1]) && print_err(1,"failed\n"))
			exit(1);
		if (pipex->n && print_err(3,"duping [", ft_itoa(pipex->n-1), "][0]\n") &&dup2(pipex->fd[pipex->n - 1][0], shell->infile) < 0 && print_err(2,"failed\n"))
			exit(1);
		if (pipex->n && print_err(3,"duping [", ft_itoa(pipex->n-1), "][0]\n") &&close(pipex->fd[pipex->n - 1][0]) && print_err(1,"failed\n"))
			exit(1);
		if (pipex->n < pipex->len && print_err(3,"closing [", ft_itoa(pipex->n), "][0]\n") &&close(pipex->fd[pipex->n][0]) && print_err(1,"failed\n"))
			exit(1);
		if (pipex->n && pipex->n < pipex->len && \
		print_err(3,"closing [", ft_itoa(pipex->n - 1),"][1]\n") &&close(pipex->fd[pipex->n - 1][1]) && printf("failed\n"))
			exit(1);
		if (!x_bi(pipex->crt, is_bi(pipex->crt[0]), shell))
			execve(pipex->cmd, pipex->crt, shell->env);
		exit(g_signal.ret);
	}
	if (pipex->n < pipex->len && close(pipex->fd[pipex->n][1]) && print_err(1,"failed\n"))
		exit(1);
	if (pipex->n && close(pipex->fd[pipex->n - 1][0]) && print_err(1,"failed\n"))
		exit(1);
}

void	pipe_exec(t_shell *shell, t_token *cmds, t_pipe *pipex)
{
	pipex->crt = cmds->cmds;
	if ((!ft_strncmp(cmds->cmds[0], "/", 1) || \
	!ft_strncmp(cmds->cmds[0], "./", 2)) && !access(cmds->cmds[0], R_OK))
		pipex->cmd = ft_strdup(pipex->crt[0]);
	else
		pipex->cmd = get_path(pipex->crt[0], \
		get_env_line(shell->env_lst, "PATH="));
	set_last_command(shell, pipex->cmd);
	pipex->pid[pipex->nb_pid] = fork();
	if (pipex->pid[pipex->nb_pid] == -1)
		return ;
	if (!pipex->pid[pipex->nb_pid])
	{
		if (!pipex->cmd && ++pipex->pipe_failed)
			exit(126 + print_err(3, "minishell: ", \
		cmds->cmds[0], ": command not found\n"));
		if (access(cmds->cmds[0], X_OK) && !ft_strncmp(cmds->cmds[0], \
	pipex->cmd, ft_strlen(cmds->cmds[0])) && ++pipex->pipe_failed)
			exit(125 + print_err(3, "minishell: ", cmds->cmds[0], \
		": Permission denied\n"));
		if (pipex->pid[pipex->nb_pid] == -1 && pipex->pipe_failed++)
			exit(1) ;
		pipe_exec2(shell, pipex);
	}
}

/*
 * if the token's type is REDIR, redirect the input/output
 * if the token's type is CMD, keep a save of the token
 * if the token's type is PIPE, execute the last command
 * if there is no pipe and the command is a builtin, execute the builtin
 * in any other cases, goes for the fork in pipe_exec
 */
void	loop_exec(t_pipe *pipex, t_token *token, t_shell *shell, int n_pipe)
{
	while (!pipex->pipe_failed && token)
	{
		if (token && token->type != CMD && token->type != PIPE)
			redirect(shell, token->filename, token->type);
		else if (token->type == CMD)
			pipex->current = token;
		else if (pipex->current && token && token->type == PIPE)
		{
			if (is_bi(pipex->current->cmds[0]) && !n_pipe && \
			set_last_command(shell, pipex->current->cmds[0]))
				x_bi(pipex->current->cmds, \
				is_bi(pipex->current->cmds[0]), shell);
			else
			{
				pipe_exec(shell, pipex->current, pipex);
				pipex->n++;
				pipex->nb_pid++;
				if (pipex->cmd)
					free(pipex->cmd);
			}
			reset_fds(shell);
			reset_std(shell);
			printf("1\n");
		}
		token = token->next;
	}
}

/*
 * execute the token
 */
void	exec_cmds(t_shell *shell, t_token *token)
{
	t_pipe	pipex;
	int		n_pipe;

	pipex.current = NULL;
	init_pipe(&pipex, token);
	n_pipe = nb_pipe(token);
	add_back(&token, new_token(NULL, NULL, PIPE));
	if (pipex.len > 400)
		return ;
	loop_exec(&pipex, token, shell, n_pipe);
	close(pipex.fd[pipex.n][1]);
	close(pipex.fd[pipex.n - 1][0]);
	pipex.i = 0;
	while (pipex.i < pipex.nb_pid)
	{
		printf("ping\n");
		waitpid(pipex.pid[pipex.i++], &pipex.status, 0);
		printf("pong\n");
		if (WIFEXITED(pipex.status))
			g_signal.ret = WEXITSTATUS(pipex.status);
		if (g_signal.ret == 96)
			g_signal.ret = 127;
	}
}
