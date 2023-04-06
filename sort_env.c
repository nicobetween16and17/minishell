/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katalbi <katalbi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 21:12:12 by niespana          #+#    #+#             */
/*   Updated: 2023/04/04 10:38:47 by katalbi          ###   ########.fr       */
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
int	env_in_alphabetic_order(t_env *env)
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
	return (0);
}

/*
 * returns the value of an environment variable or the status of the last
 * command line if s = "$?"
 */
char	*get_env(char *s, t_shell *shell)
{
	t_env	*node;
	char	*itoa_n;

	itoa_n = ft_itoa(g_signal.ret);
	ft_bzero(g_signal.str_status, 9);
	ft_strlcpy(g_signal.str_status, itoa_n, 9);
	free(itoa_n);
	if (!ft_strncmp("?", s, 2))
		return (g_signal.str_status);
	shell->tmp = ft_strjoin(s, "=");
	if (!shell->tmp)
		exit(1);
	node = get_env_side(shell->env_lst, shell->tmp, NONE);
	shell->tmp = safe_free(shell->tmp);
	if (node)
		return (node->value);
	return ("");
}

/*
 * returns the line of the environment variable (expected format NAME=)
 */
char	*get_env_line(t_env *env, char *env_line)
{
	while (env)
	{
		if (!ft_strcmp(env->name, env_line))
			return (env->value);
		env = env->next;
	}
	return (NULL);
}
