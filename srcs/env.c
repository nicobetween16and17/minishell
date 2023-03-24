/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niespana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 21:12:12 by niespana          #+#    #+#             */
/*   Updated: 2023/01/19 21:12:13 by niespana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishl.h"

void	free_tab(char **tab, int i)
{
	while (i >= 0)
		free(tab[i--]);
	free(tab);
}

char	*ft_strndup(char *s, int n)
{
	int		i;
	char	*new_s;

	i = 0;
	while (s[i] && i < n)
		i++;
	new_s = malloc((i + 1) * sizeof(char));
	if (!new_s)
		return (0);
	ft_strlcpy(new_s, s, i);
	new_s[i] = 0;
	return (new_s);
}

char	*shell_plus_one(const char *s)
{
	char	*res;
	char	*left_side;
	char	*right_side;
	int		i;
	int		nb;

	i = 0;
	while (s && s[i] && !ft_isdigit(s[i]))
		i++;
	right_side = ft_strdup(s + i);
	if (!right_side)
		return (0);
	nb = ft_atoi(right_side) + 1;
	free(right_side);
	right_side = ft_itoa(nb);
	left_side = ft_strndup((char *)s, i + 1);
	if (!left_side)
		return (0);
	res = ft_strjoin(left_side, right_side);
	free(left_side);
	free(right_side);
	return (res);
}

char	**env_init(const char **env)
{
	int		size;
	char	**res;

	size = 0;
	while (env[size])
		size++;
	res = malloc(sizeof(char *) * ++size);
	if (!res)
		return (0);
	size = -1;
	while (env[++size])
	{
		if (!ft_strncmp("SHLVL", env[size], 5))
			res[size] = shell_plus_one(env[size]);
		else
			res[size] = ft_strdup(env[size]);
		if (res && !res[size])
			free_tab(res, size);
	}
	res[size] = 0;
	return (res);
}
