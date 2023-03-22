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

char	*get_path(char *cmd, char *path)
{
	int		i;
	char	**paths;
	char	*cmd_path;
	char	*res;

	cmd_path = ft_strjoin("/", cmd);
	i = -1;
	paths = ft_split(path, ':');
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

void	init_pipe(t_pipe *pipex, t_token *cmds)
{
	pipex->pipe_failed = 0;
	pipex->i = 0;
	pipex->nb_pid = 0;
	pipex->n = 0;
	pipex->len = nb_cmd(cmds);
	if (pipex->len > 400)
		return ;
	while (!pipex->pipe_failed && pipex->n < pipex->len - 1)
	{
		if (pipe(pipex->fd[pipex->n++]))
			pipex->pipe_failed = 1;
	}
	pipex->n = 0;
}

int x_bi(char **cmd, int type, t_shell *sh)
{
	if (!type)
		return (0);
	if (type == 1)
		sh->ret = ft_echo(cmd, sh);
	if (type == 2)
		sh->ret = ft_cd(cmd, sh);
	if (type == 3)
		sh->ret = ft_pwd(cmd, sh);
	if (type == 4)
		sh->ret = ft_env(cmd, sh);
	if (type == 5)
		sh->ret = ft_unset(cmd, sh);
	if (type == 6)
		sh->ret = ft_export(cmd, sh);
	if (type == 7)
		sh->ret = ft_exit(cmd, sh);
	return (type);
}

int	is_bi(char *cmd)
{
	if (!ft_strncmp(cmd, "echo", 5))
		return (1);
	else if (!ft_strncmp(cmd, "cd", 3))
		return (2);
	else if (!ft_strncmp(cmd, "pwd", 4))
		return (3);
	else if (!ft_strncmp(cmd, "env", 4))
		return (4);
	else if (!ft_strncmp(cmd, "unset", 6))
		return (5);
	else if (!ft_strncmp(cmd, "export", 7))
		return (6);
	else if (!ft_strncmp(cmd, "exit", 5))
		return (7);
	return (0);
}

char *get_env_line(char **env, char *env_line)
{
	int i;

	i = 0;
	while (env[i] && ft_strncmp(env_line, env[i], ft_strlen(env_line)))
		i++;
	return (env[i]);
}
void	pipe_exec(t_shell *shell, t_token *cmds, t_pipe *pipex)
{
	printf("pipexec\n");
	pipex->crt = cmds->cmds;
	pipex->cmd = get_path(pipex->crt[0], get_env_line(shell->env, "PATH="));
	pipex->pid[pipex->nb_pid] = fork();
	if (pipex->pid[pipex->nb_pid] == -1)
	{
		pipex->pipe_failed = 1;
		return ;
	}
	if (pipex->pid[pipex->nb_pid] == 0)
	{
		if (pipex->n < pipex->len - 1 && \
		dup2(pipex->fd[pipex->n][1], shell->outfile) < 0)
			exit(1);
		if (pipex->n && dup2(pipex->fd[pipex->n - 1][0], shell->infile) < 0)
			exit(1);
		if (!x_bi(pipex->crt, is_bi(pipex->crt[0]), shell))
			execve(pipex->cmd, pipex->crt, shell->env);
	}
	if (pipex->n < pipex->len - 1 && close(pipex->fd[pipex->n][1]))
		exit(1);
	if (pipex->n && close(pipex->fd[pipex->n - 1][0]))
		exit(1);
}
int		custom_pipe(t_shell *sh)
{
	pid_t	pid;
	int		pipefd[2];

	pipe(pipefd);
	pid = fork();
	if (pid == 0)
	{
		if (pipefd[1] > 0)
			close(pipefd[1]);
		dup2(pipefd[0], 0);
		sh->pipe_in = pipefd[0];
		sh->pid = -1;
		sh->parent = 0;
		sh->no_exec = 0;
		return (0);
	}
	else
	{
		if (pipefd[0] > 0)
			close(pipefd[0]);
		dup2(pipefd[1], 1);
		sh->pipe_out = pipefd[1];
		sh->pid = pid;
		sh->last = 0;
		return (1);
	}
}
int	nb_pipe(t_token *t)
{
	int	i;

	i = 0;
	while (t)
	{
		if (t->type == PIPE)
			i++;
		t = t->next;
	}
	return (i);
}
void	exec_cmds(t_shell *shell, t_token *token)
{
	t_pipe	pipex;
	t_token *current;
	int	n_pipe;
	current = NULL;
	init_pipe(&pipex, token);
	n_pipe = nb_pipe(token);
	add_back(&token, new_token(NULL, NULL, PIPE));
	if (pipex.len > 400)
		return ;
	while (!pipex.pipe_failed && token)
	{
		if (token && token->type != CMD && token->type != PIPE)
			redirect(shell, token->filename, token->type);
		else if (token->type == CMD)
			current = token;
		else if (current && token && token->type == PIPE)
		{
			if (is_bi(current->cmds[0]) && !n_pipe)
				x_bi(current->cmds, is_bi(current->cmds[0]), shell);
			else
			{
				pipe_exec(shell, current, &pipex);
				pipex.n++;
				pipex.nb_pid++;
				free(pipex.cmd);
			}
			reset_fds(shell);
			reset_std(shell);
		}
		token = token->next;
	}
	close(pipex.fd[pipex.n][1]);
	close(pipex.fd[pipex.n - 1][0]);
	pipex.i = 0;
	while (pipex.i < pipex.nb_pid)
		waitpid(pipex.pid[pipex.i++], &pipex.status, 0);
}
