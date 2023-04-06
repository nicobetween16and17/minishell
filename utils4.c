/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niespana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 21:12:12 by niespana          #+#    #+#             */
/*   Updated: 2023/01/19 21:12:13 by niespana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishl.h"

void	*safe_free(void *to_free)
{
	if (to_free)
		free(to_free);
	return (NULL);
}

int	print_err(int nb_arg, ...)
{
	va_list	lst;
	int		i;

	i = -1;
	va_start(lst, nb_arg);
	while (++i < nb_arg)
		ft_putstr_fd((char *)va_arg(lst, char *), 2);
	va_end(lst);
	return (1);
}

int	last_occurence(char *s)
{
	int	last;
	int	i;

	i = -1;
	last = 0;
	while (s[++i])
	{
		if (s[i] == '>' || s[i] == '<' || s[i] == '|' || s[i] == '\n')
			last = i;
	}
	return (last);
}

void	handle_signalhdoc(int signo)
{
	g_signal.pid = waitpid(-1, &g_signal.status, WNOHANG);
	if (signo == SIGINT)
	{
		close(1);
		close(g_signal.fd_hdoc);
		g_signal.heredoc = 0;
		unlink(".heredoc.tmp");
	}
}

int	only_quotes(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
	{
		if (s[i] != '\'' && s[i] != '\"')
			return (0);
	}
	return (1);
}
