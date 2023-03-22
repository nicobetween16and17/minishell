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

char	**erase_env_var(int i, char **envp)
{
	int		j;
	int		k;
	char	**new_envp;

	k = 0;
	j = 0;
	while (envp[j])
		j++;
	new_envp = xmalloc(j * sizeof(char *));
	j = -1;
	while (envp[++j])
	{
		if (j == i)
			free(envp[i]);
		else
			new_envp[k++] = envp[j];
	}
	new_envp[k] = NULL;
	return (new_envp);
}

char	**change_var(char *s, char **envp)
{
	int	i;

	i = check_arg(s);
	if (i < 0)
		return (envp);
	i = -1;
	while (envp[++i])
	{
		if (!ft_strncmp(name_env_var(s), name_env_var(envp[i]), ft_strlen(s)))
			envp = erase_env_var(i, envp);
	}
	envp = add_back_tab(envp, s);
	return (envp);
}

int	ft_unset(char **params, t_shell *shell)
{
	int	i;
	int	check;

	i = -1;
	while (params[++i])
	{
		check = check_arg(params[i]);
		if (check > -1)
			shell->env = erase_env_var(check, shell->env);
		else if (ft_printf("invalid identifier\n"))
			return (1);
	}
	return (0);
}

int	ft_export(char **params, t_shell *shell)
{
	int	i;

	i = -1;
	if (!params)
	{
		env_in_alphabetic_order(shell->env);
		return (0);
	}
	while (params[++i])
		shell->env = change_var(params[i], shell->env);
	return (0);
}

int	ft_env(char **params, t_shell *shell)
{
	int	i;

	i = 0;
	while (params && params[i])
		i++;
	if (i > 1)
	{
		ft_putstr_fd("env: ", 1);
		ft_putstr_fd(params[0], 1);
		ft_putstr_fd(": Permission denied\n", 1);
	}
	else
	{
		i = -1;
		while (shell->env[++i])
		{
			ft_putstr_fd(shell->env[i], 1);
			ft_putstr_fd("\n", 1);
		}
	}
	return (0);
}
