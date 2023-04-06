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

/*
 * free all the element of the array from x to 0
 */
void	free_tab(char **tab, int i)
{
	while (i >= 0)
		free(tab[i--]);
	free(tab);
}

/*
 * duplicates a string until iterator n
 */
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

/*
 * returns a string of the shell level incremented, if negative, it decrements
 */
static char	*shell_plus_one(const char *s)
{
	char	*res;
	char	*left_side;
	char	*right_side;
	int		i;
	int		nb;

	i = 0;
	while (s && s[i] && (!ft_isdigit(s[i]) || s[i] == '-'))
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

/*
 * does a copy of the parent shell environment variables and increment
 * the shell level by one
 */
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

/*
 * displays all the environment variable of the current instance of the shell
 * if there is parameters to env other than env, returns an error
 */
int	ft_env(char **params, t_shell *shell)
{
	t_env	*env;

	env = shell->env_lst;
	if (params[1])
	{
		ft_putstr_fd("env: ", 1);
		ft_putstr_fd(params[1], 1);
		ft_putstr_fd(": No such file or directory\n", 1);
		return (127);
	}
	else
	{
		while (env)
		{
			ft_printf("%s%s\n", env->name, env->value);
			env = env->next;
		}
	}
	return (0);
}
