/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niespana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 21:12:12 by niespana          #+#    #+#             */
/*   Updated: 2023/01/19 21:12:13 by niespana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishl.h"

/*
 * set the type of redirection
 */
void	set_redir(char *f, t_content *c, t_token **new, t_shell *shell)
{
	char	*file;
	int		fd;

	if (!ft_strncmp(c->s, "<", 2))
		add_back(new, new_token(f, NULL, INPUT));
	else if (!ft_strncmp(c->s, "<<", 3))
	{
		fd = here_doc(f, shell);
		close(fd);
		file = ft_strdup(".heredoc.tmp");
		if (!file)
			exit(1);
		add_back(new, new_token(file, NULL, HDOC));
	}
	else if (!ft_strncmp(c->s, ">", 2))
		add_back(new, new_token(f, NULL, TRUNC));
	else if (!ft_strncmp(c->s, ">>", 3))
		add_back(new, new_token(f, NULL, APPEND));
	else
		ft_putstr_fd("Error syntax in redirection\n", 2);
}

/*
 * display an error message
 */
static int	error_open(char *file)
{
	g_signal.ret = 1;
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(file, 2);
	ft_putendl_fd(": No such file or directory", 2);
	return (1);
}

/*
 * redirect the entry or exit depending of the type of redirection
 */
void	redirect(t_shell *sh, char *f, int type)
{
	if (type == HDOC || type == INPUT)
	{
		ft_close(sh->infile);
		if (type == HDOC)
			sh->infile = open(f, O_RDONLY);
		else
			sh->infile = open(f, O_RDONLY);
		if (sh->infile == -1 && type == HDOC)
			sh->infile = open(f, O_RDWR | O_CREAT | O_TRUNC);
		else if (sh->infile == -1 && error_open(f))
			return ;
		dup2(sh->infile, 0);
		return ;
	}
	ft_close(sh->outfile);
	if (type == APPEND)
		sh->outfile = open(f, O_CREAT | O_WRONLY | O_APPEND, 0700);
	else if (type == TRUNC)
		sh->outfile = open(f, O_CREAT | O_WRONLY | O_TRUNC, 0700);
	dup2(sh->outfile, 1);
}

/*
 * return 1 if the string is composed only of '<' and '>'
 */
int	only_redir(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
	{
		if (s[i] != '>' && s[i] != '<')
			return (0);
	}
	return (1);
}

void	add_env_plus_equal(t_shell *shell, char *s)
{
	shell->tmp = ft_strjoin(s, "=");
	if (!shell->tmp)
		exit(1);
	add_env(&shell->env_lst, new_env(get_side(LEFT, shell->tmp), \
	get_side(RIGHT, shell->tmp)));
	shell->line = safe_free(shell->line);
}
