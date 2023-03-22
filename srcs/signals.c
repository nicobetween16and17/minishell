/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse0.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niespana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 21:12:12 by niespana          #+#    #+#             */
/*   Updated: 2023/01/19 21:12:13 by niespana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishl.h"

void	s_int(int value)
{
	(void)value;
	if (g_signal.pid == 0)
	{
		ft_putstr_fd("\n", 2);
		ft_putstr_fd("\033[0;32m❌ minishell > \033[0m", 2);
		g_signal.status = 1;
	}
	else
	{
		ft_putstr_fd("\n", 2);
		g_signal.status = 130;
	}
	g_signal.s_int = 1;
}

void	s_quit(int value)
{
	char	*nbr;

	nbr = ft_itoa(value);
	if (g_signal.pid != 0)
	{
		ft_putstr_fd("Quit: ", 2);
		ft_putendl_fd(nbr, 2);
		g_signal.status = 131;
		g_signal.s_quit = 1;
	}
	free(nbr);
	nbr = NULL;
}

void	init_signal(void)
{
	g_signal.s_int = 0;
	g_signal.s_quit = 0;
	g_signal.pid = 0;
	g_signal.status = 0;
}
