/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_env.c                                           :+:      :+:    :+: */
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

/*
 * switch lines
 */
char	**switch_env_var(char **envp, int i, int j)
{
	char	*tmp;

	tmp = envp[i];
	envp[i] = envp[j];
	envp[j] = tmp;
	return (envp);
}

/*
 * displays the environment variable in the alphabetical order and displays
 * "declare -x" in front of each
 */
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

/*
 * returns the value of an environment variable or the status of the last
 * command line if s = "$?"
 */
char	*get_env(char *s, char **env)
{
	int		i;
	int		j;
	char	*itoa_n;

	itoa_n = ft_itoa(g_signal.status);
	ft_bzero(g_signal.str_status, 9);
	ft_strlcpy(g_signal.str_status, itoa_n, 9);
	free(itoa_n);
	j = 0;
	i = 0;
	if (!ft_strncmp("?", s, 2))
		return (g_signal.str_status);
	while (env[i] && !find(env[i], s))
		i++;
	if (!env[i])
		return ("");
	while (env[i][j] != '=')
		++j;
	j++;
	return (env[i] + j);
}

/*
 * returns the line of the environment variable (expected format NAME=)
 */
char	*get_env_line(char **env, char *env_line)
{
	int	i;

	i = 0;
	while (env[i] && ft_strncmp(env_line, env[i], ft_strlen(env_line)))
		i++;
	return (env[i]);
}
