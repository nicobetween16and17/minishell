/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niespana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 21:12:12 by niespana          #+#    #+#             */
/*   Updated: 2023/01/19 21:12:13 by niespana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishl.h"

int	valid_identifier(char *s)
{
	int	i;
	int	first_occurence;
	int check;

	check = 0;
	first_occurence = 0;
	i = -1;
	while (s[++i])
	{
		if (!check && first_occurence)
			return (0);
		((s[i] == '=' && first_occurence++) || ((s[i] != '=' && check != '"' \
		&& check != '\'' && check != '?') && check++));
		if (!first_occurence && s[i] == '+' && s[i + 1] == '=')
			return (2);
		if (!first_occurence && !ft_isalnum(s[i]) && s[i] != '_' && \
		!(s[i] == '+' && s[i + 1] == '='))
			return (print_err(3, "minishell: export: '", s, \
			"': not a valid identifier\n") - 1);
	}
	if (!first_occurence)
		return (3);
	return (1);
}

char	*get_simplified_arg(char *s)
{
	int		i;
	int		first_occurence;
	char	*res;
	int		j;

	j = 0;
	first_occurence = 0;
	i = -1;
	res = xmalloc(ft_strlen(s) * sizeof(char));
	while (s[++i])
	{
		if (s[i] == '=')
			first_occurence = 1;
		if (first_occurence || s[i] != '+')
			res[j++] = s[i];
	}
	res[j] = 0;
	return (res);
}

void	append_env(t_env *env, char *s, t_shell *shell)
{
	char	*tmp;
	char	*tmp2;

	tmp = NULL;
	shell->tmp = get_simplified_arg(s);
	while (env)
	{
		if (!ft_strncmp(shell->tmp, env->name, ft_strlen(env->name)))
		{
			tmp2 = get_side(RIGHT, shell->tmp);
			tmp = ft_strjoin(env->value, tmp2);
			free(env->value);
			free(tmp2);
			if (!tmp)
				exit(1);
			env->value = tmp;
		}
		env = env->next;
	}
	free(shell->tmp);
}

int	set_last_command(t_shell *sh, char *path)
{
	sh->tmp = ft_strjoin("_=", path);
	if (!sh->tmp)
		exit(1);
	if (get_env_side(sh->env_lst, "_=", NONE))
		change_env(sh->env_lst, sh->tmp);
	else
		add_env(&sh->env_lst, new_env(ft_strdup("_="), ft_strdup(path)));
	free(sh->tmp);
	return (1);
}

int	empty_line(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
		if (s[i] != ' ' && s[i] != '\t')
			return (0);
	return (1);
}
