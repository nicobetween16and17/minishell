/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niespana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 21:12:12 by niespana          #+#    #+#             */
/*   Updated: 2023/01/19 21:12:13 by niespana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishl.h"

char	*get_side(int side, char *s)
{
	int		i;
	char	*res;
	int		j;

	j = 0;
	i = 0;
	while (s[i] && s[i] != '=')
		i++;
	if (side == RIGHT)
	{
		res = xmalloc(sizeof(char) * (ft_strlen(s) - i + 1));
		while (s[i] && s[++i])
			res[j++] = s[i];
		res[j] = 0;
		return (res);
	}
	res = xmalloc(sizeof(char) * (i + 2));
	i = 0;
	res[i] = s[i];
	while (s[++i] && s[i] && s[i - 1] != '=')
		res[i] = s[i];
	res[i] = 0;
	return (res);
}

int	change_env(t_env *env, char *s)
{
	while (env)
	{
		if (!ft_strncmp(s, env->name, ft_strlen(env->name)))
		{
			free(env->value);
			env->value = get_side(RIGHT, s);
			return (1);
		}
		env = env->next;
	}
	return (0);
}

t_env	*init_lst(char **tab)
{
	int		i;
	t_env	*env;

	env = new_env(NULL, NULL);
	i = -1;
	while (tab[++i])
		add_env(&env, new_env(get_side(LEFT, tab[i]), get_side(RIGHT, tab[i])));
	return (env->next);
}

/*
 * check if the parameter is a valid and existing name of environment
 * and erase the line if it is
 */
int	ft_unset(char **params, t_shell *shell)
{
	int	i;

	i = 0;
	while (params[++i])
	{
		if (remove_env(shell, params[i]))
		{
			ft_putstr_fd("invalid identifier\n", 2);
			return (1);
		}
	}
	return (0);
}

/*
 * if no parameters, shows all the environment variables
 * if parameters, for each parameters, call change_var
 */
int	ft_export(char **params, t_shell *shell)
{
	int	i;
	int	check;

	if (!params[1])
	{
		env_in_alphabetic_order(shell->env_lst);
		return (0);
	}
	i = 0;
	while (params[++i])
	{
		check = valid_identifier(params[1]);
		if (!check)
			return (1);
		if (check == 1 && !change_env(shell->env_lst, params[i]))
			add_env(&shell->env_lst, \
			new_env(get_side(LEFT, params[i]), get_side(RIGHT, params[i])));
		if (check == 2)
			append_env(shell->env_lst, params[i], shell);
		if (check == 3)
			add_env_plus_equal(shell, params[i]);
	}
	return (0);
}
