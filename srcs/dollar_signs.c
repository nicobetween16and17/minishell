/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_signs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niespana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 21:12:12 by niespana          #+#    #+#             */
/*   Updated: 2023/01/19 21:12:13 by niespana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishl.h"

char	*replace(char *str, char *start, char *end, char *replace)
{
	char	*res;
	int		i;

	i = 0;
	if ((end - start) <= 1)
		return (empty_freeable_string());
	res = malloc(sizeof(char) * (ft_strlen(str) \
	- (end - start) + ft_strlen(replace) + 1));
	while (str && *str)
	{
		if (str == start)
		{
			while (replace && *replace)
				res[i++] = *(replace++);
			str += (end - start);
		}
		if (*str)
			res[i++] = *str;
		str++;
	}
	res[i] = 0;
	return (res);
}

int	is_expandable(char *s, int i, int open)
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
	if (open)
		return (sgl || dbl);
	return (!sgl);
}

void	replace_words(t_shell *shell, int i, int j)
{
	char	*tmp2;
	char	*tmp;

	while (shell->line && shell->line[++i])
	{
		if (shell->line[i] == '$' && is_expandable(shell->line, i, 0)
			&& shell->line[i + 1] != '$'
			&& shell->line[i + 1] != ' ' && shell->line[i + 1] != '.'
			&& shell->line[i + 1] != '\'' && shell->line[i + 1] != '\"'
			&& shell->line[i + 1] != '|')
		{
			tmp2 = shell->line;
			j = i + 1;
			while (shell->line[j] != ' ' \
			&& shell->line[j] != '.' && shell->line[j] != '\'' \
			&& shell->line[j] != '\"' && shell->line[j] != '$' \
			&& shell->line[j] != '|')
				j++;
			tmp = ft_substr(shell->line, i, j - i);
			shell->line = replace(shell->line, shell->line + i, \
			shell->line + j, get_env(tmp + 1, shell->env));
			free(tmp2);
			free(tmp);
		}
	}
}
