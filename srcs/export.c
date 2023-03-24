/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
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
	new_envp = xmalloc(--j * sizeof(char *));
	j = -1;
	while (envp[++j])
	{
		if (j != i)
			new_envp[k++] = envp[j];
	}
	free(envp[j]);
	free(envp);
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

int	check_exist(char *p, char **s)
{
	int	i;

	i = -1;
	while (s[++i])
	{
		if (!ft_strncmp(p, s[i], ft_strlen(p) - 1) && s[i][ft_strlen(p)] == '=')
			return (i);
	}
	return (-1);
}

int	ft_unset(char **params, t_shell *shell)
{
	int	i;
	int	check;

	i = 0;
	while (params[++i])
	{
		check = check_exist(params[1], shell->env);
		if (check != -1)
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
	if (!params[1])
	{
		env_in_alphabetic_order(shell->env);
		return (0);
	}
	while (params[++i])
		shell->env = change_var(params[i], shell->env);
	return (0);
}
