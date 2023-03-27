/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niespana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 21:12:12 by niespana          #+#    #+#             */
/*   Updated: 2023/01/19 21:12:13 by niespana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishl.h"

/*
 * protected malloc
 */
void	*xmalloc(size_t size)
{
	void	*malloced_memory;

	malloced_memory = malloc(size);
	if (!malloced_memory)
		exit(1);
	return (malloced_memory);
}

/*
 * allocate memory for an array of strings from a linked list
 */
void	*cmds_malloc(t_list *new)
{
	int		i;

	i = 0;
	while (new && ft_strncmp((char *)new->content, "|", 2) && ++i)
		new = new->next;
	return (xmalloc(sizeof(char *) * ++i));
}

/*
 * returns the number of commands in the linked list
 */
int	nb_cmd(t_token *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		if (lst->type == CMD)
			i++;
		lst = lst->next;
	}
	return (i);
}

/*
 * free a nul terminated array of strings
 */
void	free_completed_tab(char **tab)
{
	int	i;

	i = -1;
	while (tab[++i])
		free(tab[i]);
	free(tab);
}

/*
 * returns 1 if the string only contain numerical characters else 0
 */
int	ft_strisnum(char *s)
{
	int	i;

	i = -1;
	while (s && s[++i])
		if (!ft_isdigit(s[i]))
			return (0);
	return (1);
}
