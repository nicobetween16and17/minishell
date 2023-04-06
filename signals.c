/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katalbi <katalbi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 21:12:12 by niespana          #+#    #+#             */
/*   Updated: 2023/04/04 10:56:06 by katalbi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishl.h"

/*
 * instantiate the global variable
 */
void	init_signal(void)
{
	g_signal.s_int = 0;
	g_signal.s_quit = 0;
	g_signal.pid = 0;
	g_signal.status = 0;
}

void	funtion_sigint(pid_t pid)
{
	g_signal.ret = 1;
	if (pid == -1)
	{
		ft_putstr_fd("\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else
		ft_putstr_fd("\n", 1);
}

void	funtion_sigquit(pid_t pid)
{
	char	*nbr;

	nbr = ft_itoa(g_signal.status);
	if (!nbr)
		return ;
	if (pid == -1)
	{
		rl_on_new_line();
		rl_redisplay();
		ft_putstr_fd("  \b\b", 1);
	}
	else
	{
		ft_putstr_fd("Quit: 3\n", 2);
	}
	free(nbr);
}

void	handle_signal(int signo)
{
	g_signal.pid = waitpid(-1, &g_signal.status, WNOHANG);
	if (signo == SIGINT)
		funtion_sigint(g_signal.pid);
	else if (signo == SIGQUIT)
		funtion_sigquit(g_signal.pid);
}

void	set_signal(void)
{
	if (!g_signal.heredoc)
	{
		signal(SIGINT, handle_signal);
		signal(SIGQUIT, handle_signal);
	}
	else
	{
		signal(SIGINT, handle_signalhdoc);
		signal(SIGQUIT, handle_signalhdoc);
	}
}
