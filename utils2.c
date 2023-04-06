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

/*
 * cf is_charset
 */
int	contain(char c, char *s)
{
	int	i;

	i = -1;
	if (c == '$')
	{
		while (s && s[++i])
		{
			if (s[i] == c && s[i + 1] != ' ')
				return (1);
		}
		return (0);
	}
	while (s && s[++i])
	{
		if (s[i] == c)
			return (1);
	}
	return (0);
}

/*
 * returns the of the researched environment variable
 */
int	find(char *env_line, char *to_find)
{
	int	i;

	i = 0;
	while (env_line[i] && ft_strncmp(env_line + i, to_find, ft_strlen(to_find)))
		i++;
	printf("found %s for %s\n", env_line + i, to_find);
	return (env_line[i]);
}

/*
 * returns an empty allocated string
 */
char	*empty_freeable_string(void)
{
	char	*str;

	str = xmalloc(1);
	str[0] = 0;
	return (str);
}

/*
 * returns the iterator of the argument, -1 if it does not exist
 */
int	check_arg(char *s)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != '=')
		i++;
	if (s[i] == '=' && i == 0)
		return (-1);
	if (s[i] == 0)
		return (-1);
	return (i);
}

/*
 * returns a copy of the string left side (format being NAME=VALUE), NULL if
 * not valid
 */
char	*name_env_var(char *s)
{
	int		i;
	char	*new;

	i = 0;
	while (s[i] && s[i] != '=')
		i++;
	if (s[i] != '=')
	{
		ft_putstr_fd(s, 2);
		ft_putstr_fd(" : not a valid identifier\n", 2);
		return (NULL);
	}
	new = ft_strndup(s, i + 1);
	return (new);
}
