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

t_env	*get_next_smallest(t_env *env, char *last)
{
	t_env	*save;

	save = NULL;
	while (env)
	{
		if (ft_strncmp(env->name, last, ft_strlen(env->name)) > 0 && \
		(!save || ft_strncmp(env->name, save->name, ft_strlen(env->name)) < 0))
		save = env;
		env = env->next;
	}
	return (save);
}

/*
 * displays the environment variable in the alphabetical order and displays
 * "declare -x" in front of each
 */
void	env_in_alphabetic_order(t_env *env)
{
	char	*last;
	t_env	*current;

	last = "\0";
	while (1)
	{
		current = get_next_smallest(env, last);
		if (current)
			last = current->name;
		else
			break ;
		ft_printf("declare -x %s%s\n", current->name, current->value);
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
