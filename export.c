/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbierny <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 22:18:13 by gbierny           #+#    #+#             */
/*   Updated: 2023/01/10 22:18:57 by gbierny          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishl.h"


char *ft_strndup(char *s, int n)
{
    int i;
    char *new_s;
    i = 0;
    while (s[i] && i < n)
        i++;
    new_s = malloc((i + 1) * sizeof(char));
    if (!new_s)
    {
        printf("error");
        exit(0);
    }
    ft_strlcpy(new_s, s, i);
    new_s[i] = 0;
    return (new_s);
}

int check_arg(char *s)
{
	int i;

	i = 0;
	while (s[i] && s[i] != '=')
		i++;
	if (s[i] == '=' && i == 0)
	{
		printf("invalid identifier");
		exit(0);
	}
	if (s[i] == 0)
		return (-1);
	return (i);
}



char *name_env_var(char *s)
{
    int i;
    char *new;
    i = 0;
    while (s[i] && s[i] != '=')
        i++;
    if (s[i] != '=')
    {
        printf("not a valid identifier");
        exit(0);
    }
    new = ft_strndup(s, i + 1);
    return (new);
}

char **add_back_tab(char **tab, char *s)
{
    int i;
    char **new_tab;

    i = 0;
    while(tab[i])
        i++;
    new_tab = malloc((i + 2) * sizeof(char *));
    i = -1;
    while (tab[++i])
        new_tab[i] = tab[i];
    new_tab[i] = ft_strdup(s);
    new_tab[i + 1] = NULL;
    return (new_tab);
}
char **erase_env_var(int i, char **envp)
{
	int j;
	char **new_envp;

	j = 0;
	while (envp[j])
		j++;
	new_envp = malloc(j * sizeof(char*));
	if (!new_envp)
	{
		printf("malloc problem");
		exit(0);
	}
	j = -1;
	while(++j < i)
		new_envp[j] = envp[j];
	while (envp[++j])
		new_envp[j] = envp[j];
	new_envp[j] = NULL;
	return (new_envp);
}
char **change_var(char *s, char **envp)
{
	int i;

	i = 0;
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




void	ft_unset(char **params, t_shell *shell)
{
	int	i;
	int	check;
	i = -1;
	while (params[++i])
	{
		check = check_arg(params[i]);
		if (check > -1)
		{
			shell->env = erase_env_var(check, shell->env);
		}
	}
}
void	ft_export(char **params, t_shell *shell)
{
	int i;

	i = 0;
	if (!params)
	{
		env_in_alphabetic_order(shell->env);
		return ;
	}
	while (params[i])
	{
		shell->env = change_var(params[i], shell->env);
		i++;
	}
}
void	ft_env(char **params, t_shell *shell)
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
}