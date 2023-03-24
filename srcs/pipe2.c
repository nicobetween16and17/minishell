/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niespana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 21:12:12 by niespana          #+#    #+#             */
/*   Updated: 2023/01/19 21:12:13 by niespana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishl.h"

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

int	x_bi(char **cmd, int type, t_shell *sh)
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
