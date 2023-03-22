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

char	*sub(char *s, int start, int len)
{
	t_utils2	u;

	printf("%s %d\n", s + start, len);
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
		if (((!is_btwn_q(s, u.i) && s[u.i] != '\'' && s[u.i] != '\"' && s[u.i] != ' ') || is_btwn_q(s, u.i)))
			u.sub[u.j++] = s[u.i];
	}
	u.sub[u.j] = 0;
	return (u.sub);
}

int	is_charset(char c, char *charset)
{
	while (charset && *charset)
		if (c == *charset++)
			return (1);
	return (0);
}
