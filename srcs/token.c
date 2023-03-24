/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niespana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 21:12:12 by niespana          #+#    #+#             */
/*   Updated: 2023/01/19 21:12:13 by niespana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishl.h"

/*
 * create a new token and initiate the value with ones given
 */
t_token	*new_token(char *filename, char **cmds, int type)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (0);
	new->filename = filename;
	new->cmds = cmds;
	new->type = type;
	new->next = NULL;
	return (new);
}

/*
 * returns the size of the linked list
 */
int	token_size(t_token *lst)
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
t_token	*last_token(t_token *lst)
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
int	add_back(t_token **lst, t_token *new)
{
	t_token	*tmp;

	if (*lst == NULL)
		*lst = new;
	else
	{
		tmp = last_token(*(lst));
		tmp->next = new;
	}
	return (1);
}

/*
 * increment token
 */
int	next_token(t_list **token)
{
	*token = (*token)->next;
	return (1);
}
