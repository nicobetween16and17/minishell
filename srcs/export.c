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

/*
 * Create a new array of size -1, select the iterator of the environment
 * variable and copy everything except this one into the new array and
 * returns it
 */
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

/**
 * check if the argument is incorrect, return the already existing
 * environment variables, if it is correct, if it exists already
 * change the value by the new one, if it is brand new, return a
 * new array with size + 1 and a new line for the variable
 */
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

/*
 * returns the iterator of the environment variable. -1 if it does not exist
 */
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

/*
 * check if the parameter is a valid and existing name of environment
 * and erase the line if it is
 */
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

/*
 * if no parameters, shows all the environment variables
 * if parameters, for each parameters, call change_var
 */
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
