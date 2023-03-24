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

int	find(char *env_line, char *to_find)
{
	int	i;

	i = 0;
	while (env_line[i] && ft_strncmp(env_line + i, to_find, ft_strlen(to_find)))
		i++;
	return (env_line[i]);
}

char	*empty_freeable_string(void)
{
	char	*str;

	str = malloc(1);
	str[0] = 0;
	return (str);
}

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
