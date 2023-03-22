/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse0.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niespana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 21:12:12 by niespana          #+#    #+#             */
/*   Updated: 2023/01/19 21:12:13 by niespana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishl.h"

int	cut_until(char *s, t_utils *utils, char *stop)
{
	int	start;
	int	len;

	len = 1;
	start = utils->i;
	if (stop == NULL)
	{
		stop = &s[utils->i];
		while (s[utils->i + len] && s[utils->i + len] == stop[0])
			len++;
	}
	else
	{
		while (s[start + len] && (!is_charset(s[start + len], stop) ||
				is_btwn_q(s, start + len)))
			len++;
	}
	utils->tmp = sub(s, start, len);
	if (ft_strlen(utils->tmp))
		ft_lstadd_back(&utils->tokens, ft_lstnew(utils->tmp));
	else
		free(utils->tmp);
	utils->i += len;
	return (1);
}

int	set_last(t_utils *utils, int i)
{
	utils->last = i;
	return (1);
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
}

void	setup_cmd(t_list *t, t_token **new, char *f, int i)
{
	char	**cmds;

	while (t)
	{
		if ((((char *)t->content)[0] == '>' || ((char *)t->content)[0] == '<'))
		{
			if (t->next)
				f = (char *)t->next->content;
			set_redir(f, t, new);
			t = t->next;
		}
		else if (f && t && !ft_strncmp((char *)t->content, f, ft_strlen(f + 1)))
			t = t->next;
		else if (t && !ft_strncmp((char *)t->content, "|", 2))
		{
			add_back(new, new_token(NULL, NULL, PIPE));
			t = t->next;
		}
		else
		{
			cmds = cmds_malloc(t);
			i = 0;
			while (t && ft_strncmp((char *)t->content, "|", 2) \
			&& ((char *)t->content)[0] != '>' && ((char *)t->content)[0] != '<')
				(!(!(cmds[i++] = t->content)) && next_token(&t));
			(!(cmds[i] = 0) && add_back(new, new_token(NULL, cmds, CMD)));
		}

	}
}

void	parse(char *s, t_shell *sh)
{
	t_utils	utils;

	utils.last = 0;
	utils.tokens = ft_lstnew(NULL);
	utils.i = 0;
	utils.cmd = 1;
	while (s[utils.i])
	{
		((((s[utils.i] == '<' || s[utils.i] == '>') && set_last(&utils, 1) &&\
		!is_btwn_q(s, utils.i) && cut_until(s, &utils, NULL)) || \
		(s[utils.i] == '|' && set_last(&utils, 1) && !is_btwn_q(s, utils.i) && \
		cut_until(s, &utils, NULL)) || (utils.i == 0 && !is_btwn_q(s, utils.i) \
		&& cut_until(s, &utils, " ")) || ((s[utils.i] == ' ' || !s[utils.i] || \
		(utils.last && set_last(&utils, 0))) && !is_btwn_q(s, utils.i) && \
		cut_until(s, &utils, " |<>")) || ++utils.i));
	}
	utils.tmp = "";
	utils.tokens = utils.tokens->next;
	sh->tokens = new_token(NULL, NULL, -1);
	setup_cmd(utils.tokens, &sh->tokens, utils.tmp, 0);
}
