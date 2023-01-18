/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niespana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 15:05:02 by niespana          #+#    #+#             */
/*   Updated: 2023/01/13 15:05:04 by niespana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include "minishl.h"
#include "libft/libft.h"


void display(t_list *test)
{
	while (test)
	{
		printf("test = %s\n", (char *)test->content);
		test = test->next;
	}

}
void	adding(t_list *test)
{
	test = ft_lstnew("test");
	ft_lstadd_back(&test, ft_lstnew("test0"));
	ft_lstadd_back(&test, ft_lstnew("test1"));
	display(test);
}
int	main(int ac, char **av, char **env)
{
	t_list *test;

	test = NULL;
	adding(test);
	printf("adding is finished\n");
	display(test);
	printf("display is finihed\n");
}
