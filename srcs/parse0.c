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

/*
 * cut the part of the command line and erase the quotes except the one
 * that are situated between opposed quotes
 */
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
		while (s[start + len] && (!is_charset(s[start + len], stop) || \
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

/*
 * simple flag to say when you found a keyword
 */
int	set_last(t_utils *utils, int i)
{
	utils->last = i;
	return (1);
}

/*
 * create an easy to une cmd with the arguments
 */
t_list	*fill_cmd_tab(t_list *t, t_token **new, int i)
{
	char	**cmds;

	cmds = cmds_malloc(t);
	i = 0;
	while (t && ft_strncmp((char *)t->content, "|", 2) \
			&& !only_redir((char *)t->content))
		(!(!(cmds[i++] = t->content)) && next_token(&t));
	(!(cmds[i] = 0) && add_back(new, new_token(NULL, cmds, CMD)));
	return (t);
}

/*
 * depending of the features of the token, create the complete token with a type
 */
void	setup_cmd(t_list *t, t_token **new, char *f, int i)
{
	while (t)
	{
		if (only_redir((char *)t->content))
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
			t = fill_cmd_tab(t, new, i);
	}
}

/*
 * parse through the line and cut when encounter some key words, remove the
 * quotes too. then create type for the tokens.
 */
void	parse(char *s, t_shell *sh)
{
	t_utils	utils;

	utils.last = 0;
	utils.tokens = ft_lstnew(NULL);
	utils.i = 0;
	utils.cmd = 1;
	while (s[utils.i])
	{
		((((s[utils.i] == '<' || s[utils.i] == '>') && set_last(&utils, 1) && \
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
	ft_lstclear(&utils.tokens, free);
}
