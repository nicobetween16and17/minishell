/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_node.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niespana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 21:12:12 by niespana          #+#    #+#             */
/*   Updated: 2023/01/19 21:12:13 by niespana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishl.h"

/*
 * take an env name and return either the env_list containing that
 * value or one of the adjacent node depending on the macro given
 * in the variable side.
 */
t_env	*get_env_side(t_env *env_lst, char *s, int side)
{
	if (side == RIGHT)
	{
		while (env_lst && ft_strncmp(env_lst->name, s, ft_strlen(s)))
			env_lst = env_lst->next;
		if (env_lst)
			env_lst = env_lst->next;
	}
	else if (side == LEFT)
	{
		while (env_lst && env_lst->next && \
		ft_strncmp(env_lst->next->name, s, ft_strlen(s)))
			env_lst = env_lst->next;
	}
	else
	{
		while (env_lst && ft_strncmp(env_lst->name, s, ft_strlen(s)))
			env_lst = env_lst->next;
	}
	return (env_lst);
}

int	remove_env(t_shell *sh, char *s)
{
	t_env	*removed;
	t_env	*head;
	t_env	*previous;
	t_env	*next;

	sh->tmp = ft_strjoin(s, "=");
	head = sh->env_lst;
	removed = get_env_side(sh->env_lst, sh->tmp, 0);
	previous = get_env_side(sh->env_lst, sh->tmp, LEFT);
	next = get_env_side(sh->env_lst, sh->tmp, RIGHT);
	free(sh->tmp);
	if (!removed)
		return (1);
	free(removed->name);
	free(removed->value);
	free(removed);
	if (previous->next == NULL)
		sh->env_lst = next;
	else
	{
		sh->env_lst = previous;
		sh->env_lst->next = next;
		sh->env_lst = head;
	}
	return (0);
}

int	get_env_size(t_env *env)
{
	int	i;

	i = 0;
	while (env)
	{
		i++;
		env = env->next;
	}
	return (i);
}

char	**get_env_tab(t_env *env)
{
	int		i;
	char	**tab;

	i = get_env_size(env);
	tab = xmalloc(sizeof(char *) * (i + 1));
	i = 0;
	while (env)
	{
		tab[i++] = ft_strjoin(env->name, env->value);
		env = env->next;
	}
	tab[i] = 0;
	return (tab);
}

void	free_env_lst(t_env *env)
{
	t_env	*mem;

	if (env)
		mem = env->next;
	while (env)
	{
		free(env->name);
		free(env->value);
		free(env);
		env = mem;
		if (env)
			mem = env->next;
	}
}
