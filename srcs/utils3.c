/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niespana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 21:12:12 by niespana          #+#    #+#             */
/*   Updated: 2023/01/19 21:12:13 by niespana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishl.h"

static int	set_err(t_err *er, int error)
{
	er->err = error;
	return (error);
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

int	check_forbidden(char *s, t_shell *sh)
{
	int	i;
	int	e;

	e = 0;
	i = -1;
	while (s[++i])
	{
		if (s[i] == '>' || s[i] == '<' || s[i] == '|')
			i = handle_error(s, i, &e);
		if (e)
		{
			sh->ret = e;
			ft_putstr_fd("shell: syntax error near unexptected token \'", 2);
			ft_putchar_fd(s[i], 2);
			ft_putstr_fd("\'\n", 2);
			return (1);
		}
	}
	return (0);
}
