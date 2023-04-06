/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katalbi <katalbi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 21:12:12 by niespana          #+#    #+#             */
/*   Updated: 2023/04/04 11:43:30 by katalbi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishl.h"

/*
 * instantiate the pipes, the number of the commands, the iterator, the boolean
 * that checks if the pipe failed, the current pipe and the number of pid
 */
void	init_pipe(t_pipe *pipex, t_token *cmds)
{
	pipex->pipe_failed = 0;
	pipex->i = 0;
	pipex->nb_pid = 0;
	pipex->n = 0;
	pipex->len = nb_pipe(cmds);
	if (pipex->len > 400)
		return ;
	while (!pipex->pipe_failed && pipex->n < pipex->len)
	{
		if (pipe(pipex->fd[pipex->n++]))
			pipex->pipe_failed = 1;
	}
	pipex->n = 0;
}

/*
 * execute the builtin depending of the type
 */
int	x_bi(char **cmd, int type, t_shell *sh)
{
	if (!type)
		return (0);
	if (type == 1)
		g_signal.ret = ft_echo(cmd, sh);
	if (type == 2)
		g_signal.ret = ft_cd(cmd, sh);
	if (type == 3)
		g_signal.ret = ft_pwd(cmd, sh);
	if (type == 4)
		g_signal.ret = ft_env(cmd, sh);
	if (type == 5)
		g_signal.ret = ft_unset(cmd, sh);
	if (type == 6)
		g_signal.ret = ft_export(cmd, sh);
	if (type == 7)
		g_signal.ret = ft_exit(cmd, sh);
	return (type);
}

/*
 * returns a number between 1 and 7 if it is a builtin else 0
 */
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

/*
 * returns the number of pipes
 */
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

int	is_catcatls(t_token *tokens)
{
	int	cat;
	int	ls;

	cat = 0;
	ls = 0;
	while (tokens)
	{
		if (tokens->type == CMD)
		{
			if (ft_strcmp(tokens->cmds[0], "cat"))
				cat++;
			if (ft_strcmp(tokens->cmds[0], "ls"))
				ls++;
		}
		tokens = tokens->next;
	}
	return (cat >= 2 && ls);
}
