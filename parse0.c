/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse0.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katalbi <katalbi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 21:12:12 by niespana          #+#    #+#             */
/*   Updated: 2023/04/04 11:31:16 by katalbi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishl.h"

void	cut_until2(char *s, t_utils *utils, t_utils3 *u)
{
	utils->content->s = sub(s, u->start, u->len);
	utils->content->quotes = has_quotes(s, u->len, u->start);
	if (ft_strlen(utils->content->s) || (only_redir(u->previous->s) && \
	utils->content->quotes))
		ft_lstadd_back(&utils->tokens, ft_lstnew((void *)utils->content));
	else
	{
		utils->content->s = safe_free(utils->content->s);
		utils->content = safe_free(utils->content);
	}
	utils->i += u->len;
}

/*
 * cut the part of the command line and erase the quotes except the one
 * that are situated between opposed quotes
 */
int	cut_until(char *s, t_utils *utils, char *stop)
{
	t_utils3	u;

	u.last = ft_lstlast(utils->tokens);
	if (u.last)
		u.previous = (t_content *)u.last->content;
	utils->content = malloc(sizeof(t_content));
	u.len = 1;
	u.start = utils->i;
	if (stop == NULL)
	{
		stop = &s[utils->i];
		while (s[utils->i + u.len] && s[utils->i + u.len] == stop[0])
			u.len++;
	}
	else
	{
		while (s[u.start + u.len] && (!is_charset(s[u.start + u.len], stop) || \
		is_btwn_q(s, u.start + u.len)))
			u.len++;
	}
	cut_until2(s, utils, &u);
	return (1);
}

void	setup_cmd2(t_list **t, t_utils4 *u, t_shell *shell)
{
	if (only_redir(u->crt->s) && !u->crt->quotes)
	{
		if (u->nxt)
			u->f = u->nxt->s;
		if (!u->f || !ft_strlen(u->f))
			set_redir("", u->crt, &shell->tokens, shell);
		else
			set_redir(u->f, u->crt, &shell->tokens, shell);
		next_token(t);
	}
	else if (u->f && !ft_strcmp(u->crt->s, u->f))
		*t = (*t)->next;
	else if (!ft_strcmp(u->crt->s, "|") && !u->crt->quotes)
	{
		safe_free(u->crt->s);
		safe_free(u->crt);
		add_back(&shell->tokens, new_token(NULL, NULL, PIPE));
		next_token(t);
	}
	else
		*t = fill_cmd_tab(*t, &shell->tokens, u->i);
}

/*
 * depending of the features of the token, create the complete token with a type
 */
void	setup_cmd(t_list *t, t_shell *shell, char *f, int i)
{
	t_list		*head;
	t_utils4	u;

	u.f = f;
	u.i = i;
	head = t;
	while (t)
	{
		u.crt = (t_content *)t->content;
		if (t->next)
			u.nxt = (t_content *)t->next->content;
		else
			u.nxt = NULL;
		setup_cmd2(&t, &u, shell);
	}
	free_lst(head);
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
		&& cut_until(s, &utils, " |")) || ((s[utils.i] == ' ' || !s[utils.i] || \
		(utils.last && set_last(&utils, 0))) && !is_btwn_q(s, utils.i) && \
		cut_until(s, &utils, " |<>")) || ++utils.i));
	}
	utils.tmp = "";
	utils.tokens = utils.tokens->next;
	sh->tokens = new_token(NULL, NULL, -1);
	setup_cmd(utils.tokens, sh, utils.tmp, 0);
}
