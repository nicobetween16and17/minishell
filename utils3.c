/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katalbi <katalbi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 21:12:12 by niespana          #+#    #+#             */
/*   Updated: 2023/04/04 10:38:29 by katalbi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishl.h"

static int	set_err(t_err *er, int error)
{
	er->err = error;
	return (error);
}

int	has_words(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
	{
		if (s[i] != '>' && s[i] != '<' && s[i] != '|' && s[i] != ' ')
			return (1);
	}
	return (0);
}

int	check_filenames(char *s)
{
	int	i;
	int	res;

	res = 1;
	i = 0;
	while (s[i])
	{
		if (!is_btwn_q(s, i) && (s[i] == '>' || s[i] == '<'))
		{
			while (s[i] && (s[i] == '>' || s[i] == '<'))
				i++;
			while (s[i] && s[i] == ' ')
				i++;
			if (!(s[i] && s[i] != '>' && s[i] != '<' && s[i] != '|'))
				res = 0;
		}
		i++;
	}
	return (res);
}

static int	handle_error(char *s, int i, int *e)
{
	t_err	er;

	er.rep = 0;
	er.err = 0;
	er.c = s[i];
	while (s[++i] && (s[i] == '>' || s[i] == '<' || s[i] == '|'))
	{
		if (er.c == '|' && s[i] == '|' && set_err(&er, 1))
			break ;
		if (((er.c == '>' && s[i] == '<') || (er.c == '<' && s[i] == '>')) && \
		set_err(&er, 258))
			break ;
		if ((er.c == '>' && s[i] == '>') || (er.c == '<' && s[i] == '<'))
			er.rep++;
		if (er.rep > 1 && set_err(&er, 258))
			break ;
	}
	*e = er.err;
	return (i);
}

int	check_forbidden(char *s)
{
	int	i;
	int	e;

	e = 0;
	i = -1;
	if (!ft_strlen(s))
		return (0);
	if (only_quotes(s) && print_err(1, \
	"minishell: : command not found\n"))
		return (set_error(127));
	if (!has_words(s) || !check_filenames(s))
		return (print_err(4, "minishell: syntax error ", \
		"near unexpected token \'", &s[last_occurence(s)], "\'\n"));
	while (s[++i])
	{
		if ((s[i] == '>' || s[i] == '<' || s[i] == '|') && !is_btwn_q(s, i))
			i = handle_error(s, i, &e);
		if (e)
		{
			g_signal.ret = e;
			return (print_err(3, "minishell: syntax error near unexptected token \'", \
			&s[i], "\'\n") + set_error(1) - 1);
		}
	}
	return (0);
}
