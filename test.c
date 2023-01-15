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

typedef struct path
{
	int	coins;
	int	exit;
}	t_path;


int	main(int ac, char **av, char **env)
{
	char *test = "\"la s'tri'ng\"'l'autre string'";
	printf("%d\n", is_expandable(test, strlen(test), 1));
	printf("%d\n", is_expandable(test, 4, 0));
}
