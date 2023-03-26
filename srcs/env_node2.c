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

t_env	*new_env(char *name, char *value)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (0);
	new->name = name;
	new->value = value;
	new->next = NULL;
	return (new);
}

/*
 * returns the size of the linked list
 */
int	env_size(t_env *lst)
{
	int		size;

	size = 1;
	if (!lst)
		return (0);
	while (lst->next)
	{
		lst = lst->next;
		size++;
	}
	return (size);
}

/*
 * returns last token of the list
 */
t_env	*last_env(t_env *lst)
{
	if (!lst)
		return (lst);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

/*
 * add the token at the end of the linked list
 */
int	add_env(t_env **lst, t_env *new)
{
	t_env	*tmp;

	if (*lst == NULL)
		*lst = new;
	else
	{
		tmp = last_env(*(lst));
		tmp->next = new;
	}
	return (1);
}
