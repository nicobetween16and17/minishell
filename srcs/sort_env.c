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

char	*print_name_variable(char *s)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != '=')
		i++;
	write(1, s, i);
	return (s + i + 1);
}

char	**switch_env_var(char **envp, int i, int j)
{
	char	*tmp;

	tmp = envp[i];
	envp[i] = malloc(sizeof(char) * (ft_strlen(envp[j] + 1)));
	if (!envp[i])
	{
		printf("malloc probleme");
		exit(0);
	}
	envp[i] = envp[j];
	envp[j] = malloc(sizeof(char) * (ft_strlen(tmp) + 1));
	if (!envp[j])
	{
		printf("malloc error");
		exit(0);
	}
	envp[j] = tmp;
	return (envp);
}

void	env_in_alphabetic_order(char **envp)
{
	int		i;
	int		j;
	char	*s;

	i = -1;
	while (envp[++i])
	{
		j = i;
		while (envp[j + 1])
		{
			if (ft_strncmp(envp[i], envp[j], ft_strlen(envp[i])) > 0)
				envp = switch_env_var(envp, i, j);
			j++;
		}
	}
	i = 0;
	while (envp[i])
	{
		ft_putstr_fd("declare -x ", 1);
		s = print_name_variable(envp[i]);
		ft_putstr_fd("=\"", 1);
		ft_putstr_fd(s, 1);
		ft_putstr_fd("\"\n", 1);
		i++;
	}
}

char	*get_env(char *s, char **env)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (env[i] && !find(env[i], s))
		i++;
	if (!env[i])
		return ("");
	while (env[i][j] != '=')
		++j;
	j++;
	return (env[i] + j);
}
