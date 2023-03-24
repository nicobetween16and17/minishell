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

char	**add_back_tab(char **tab, char *s)
{
	int		i;
	char	**new_tab;

	i = 0;
	while (tab[i])
		i++;
	new_tab = malloc((i + 2) * sizeof(char *));
	i = -1;
	while (tab[++i])
		new_tab[i] = tab[i];
	new_tab[i] = ft_strdup(s);
	new_tab[i + 1] = NULL;
	return (new_tab);
}

void	set_redir(char *f, t_list *tokens, t_token **new)
{
	if (!ft_strncmp((char *)tokens->content, "<", 2))
		add_back(new, new_token(f, NULL, INPUT));
	else if (!ft_strncmp((char *)tokens->content, "<<", 3))
	{
		here_doc(f);
		add_back(new, new_token(f, NULL, HDOC));
	}
	else if (!ft_strncmp((char *)tokens->content, ">", 2))
		add_back(new, new_token(f, NULL, TRUNC));
	else if (!ft_strncmp((char *)tokens->content, ">>", 3))
		add_back(new, new_token(f, NULL, APPEND));
	else
		ft_printf("Error syntax in redirection\n");
}

int	error_open(char *file, t_shell *sh)
{
	sh->ret = 1;
	sh->no_exec = 1;
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(file, 2);
	ft_putendl_fd(": No such file or directory", 2);
	return (1);
}

void	redirect(t_shell *sh, char *f, int type)
{
	if (type == HDOC || type == INPUT)
	{
		ft_close(sh->infile);
		if (type == HDOC)
			sh->infile = open(".heredoc.tmp", O_RDONLY);
		else
			sh->infile = open(f, O_RDONLY);
		if (sh->infile == -1 && error_open(f, sh))
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
