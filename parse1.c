/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niespana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 21:12:18 by niespana          #+#    #+#             */
/*   Updated: 2023/01/19 21:12:20 by niespana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishl.h"

/*
 * create an easy to une cmd with the arguments
 */
t_list	*fill_cmd_tab(t_list *t, t_token **new, int i)
{
	char		**cmds;
	t_content	*crt;

	crt = t->content;
	cmds = cmds_malloc(t);
	i = 0;
	while (t && (crt->quotes || (ft_strncmp(crt->s, "|", 2) && \
	!only_redir(crt->s))))
	{
		cmds[i++] = crt->s;
		t = t->next;
		if (t)
			crt = t->content;
	}
	(!(cmds[i] = 0) && add_back(new, new_token(NULL, cmds, CMD)));
	return (t);
}

int	has_quotes(char *s, int len, int start)
{
	int	i;
	int	stop;

	stop = -1;
	i = start;
	while (s[i] && ++stop < len)
	{
		if (is_btwn_q(s, i) || \
		(!is_btwn_q(s, i) && (s[i] == '\'' || s[i] == '\"')))
			return (1);
		i++;
	}
	return (0);
}

/*
 * returns 1 if the iterator point to a char of a string that is between
 * quotes. the start and end quotes are consider as outside of the quote
 */
int	is_btwn_q(char *s, int i)
{
	int	sgl;
	int	dbl;
	int	j;

	sgl = 0;
	dbl = 0;
	j = -1;
	while (s && s[++j] && j < i)
	{
		((!sgl && !dbl && s[j] == '\"' && ++dbl) || (!dbl && !sgl \
		&& s[j] == '\'' && ++sgl) || (!sgl && dbl && s[j] == '\"' \
		&& dbl--) || (!dbl && sgl && s[j] == '\'' && sgl--));
	}
	if ((sgl && s[j] == '\'') || (dbl && s[j] == '\"'))
		return (0);
	return (sgl || dbl);
}

/*
 * create a substring without the useless quotes
 */
char	*sub(char *s, int start, int len)
{
	t_utils2	u;

	u.f = 0;
	u.j = 0;
	u.nbq = 0;
	u.i = -1 + start;
	while (s[++u.i] && u.i < len)
		if (!is_btwn_q(s, u.i) && (s[u.i] == '\"' || s[u.i] == '\''))
			u.nbq++;
	u.i = -1 + start;
	u.sub = xmalloc(sizeof(char) * (len + 1 - u.nbq));
	while (s[++u.i] && u.i < start + len)
	{
		if (((!is_btwn_q(s, u.i) && s[u.i] != '\'' && s[u.i] != '\"' && \
		s[u.i] != ' ') || is_btwn_q(s, u.i)))
			u.sub[u.j++] = s[u.i];
	}
	u.sub[u.j] = 0;
	return (u.sub);
}

/*
 * return 1 if the character is in the charset else 0
 */
int	is_charset(char c, char *charset)
{
	while (charset && *charset)
		if (c == *charset++)
			return (1);
	return (0);
}
