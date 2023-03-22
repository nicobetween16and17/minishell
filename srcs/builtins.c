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

int	ft_cd(char **params, t_shell *shell)
{
	int		dir;
	char	*path;

	if (!params || !params[0] || !params[1])
		return (1);
	path = params[1];
	(void)shell;
	dir = chdir(path);
	if (dir)
		ft_printf("cd: string not in pwd: %s\n", path);
	return (0);
}

int	ft_pwd(char **params, t_shell *shell)
{
	char	*buf;

	(void)params;
	(void)shell;
	buf = getcwd(NULL, 0);
	ft_putstr_fd(buf, 1);
	write(1, "\n", 1);
	free(buf);
	return (0);
}

static int	nb_args(char **args)
{
	int		size;

	size = 0;
	while (args[size])
		size++;
	return (size);
}

int	ft_echo(char **args, t_shell *shell)
{
	int		i;
	int		n_option;

	(void)shell;
	i = 1;
	n_option = 0;
	if (nb_args(args) > 1)
	{
		while (args[i] && ft_strncmp(args[i], "-n", 3) == 0)
		{
			n_option = 1;
			i++;
		}
		while (args[i])
		{
			ft_putstr_fd(args[i], 1);
			if (args[i + 1] && args[i][0] != '\0')
				write(1, " ", 1);
			i++;
		}
	}
	if (n_option == 0)
		write(1, "\n", 1);
	return (0);
}

int	ft_exit(char **params, t_shell *shell)
{
	shell->exit = 1;
	ft_bzero(shell->folie, 10);
	ft_putstr_fd("exit ", 2);
	ft_strlcpy(shell->folie, "✔️ ", 8);
	if (params[1])
		ft_strlcpy(shell->folie, "❌ ", 8);
	ft_putendl_fd(shell->folie, 2);
	if (params[1] && params[2])
	{
		shell->ret = 1;
		ft_putendl_fd("minishell: exit: too many arguments", 2);
	}
	else if (params[1] && ft_strisnum(params[1]) == 0)
	{
		shell->ret = 255;
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(params[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
	}
	else if (params[1])
		shell->ret = ft_atoi(params[1]);
	else
		shell->ret = 0;
	return (0);
}