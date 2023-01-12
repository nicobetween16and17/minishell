#include "minishl.h"

void	handle(int signal);

int	contain(char c, char *s)
{
	int	i;

	i = -1;
	if (c == '$')
	{
		while (s && s[++i])
		{
			if (s[i] == c && s[i + 1] != ' ')
				return (1);
		}
		return (0);
	}
	while (s && s[++i])
	{
		if (s[i] == c)
			return (1);
	}
	return (0);
}

int	find(char *env_line, char *to_find)
{
	while (*env_line && ft_strncmp(env_line, to_find, ft_strlen(to_find)))
		env_line++;
	return (*env_line);
}

char	*get_env(char *s, char **env)
{
	int	i;

	i = 0;
	while (env[i] && !find(env[i], s))
		i++;
	if (!env[i])
		return ("");
	while (*(env[i]) != '=')
		env[i]++;
	env[i]++;
	return (env[i]);
}

char	*get_replacement(char *s1, t_shell *shell)
{
	int i;
	int j;
	char *s2;

	i = 0;
	j = -1;
	while (s1 && s1[i] != ' ' && s1[i] != 0)
		i++;
	s2 = malloc(sizeof(char) * (i + 1));
	while (i > ++j)
		s2[j] = s1[j];
	return (get_env(s2, shell->env));
}

char	*empty_freeable_string()
{
	char *str;

	str = malloc(1);
	str[0] = 0;
	return (str);
}

char	*replace(char *str, char *search, char *replace)
{
	char	*res;
	char	*start;
	int		i;

	printf("REPLACE %s\n", replace);
	i = 0;
	if (strlen(search) <= 1)
		return (empty_freeable_string());
	search++;
	start = ft_strnstr(str, search, ft_strlen(str));
	res = malloc(sizeof(char) * (ft_strlen(str)
		- ft_strlen(search) + ft_strlen(replace) + 1));
	while (str && *str)
	{
		printf("%s == %s\n", str, start);
		if (str == start && printf("found equality\n"))
		{
			while (replace && *replace)
				res[i++] = *(replace++);
			printf("%s\n%s\n", str, res);
			str += ft_strlen(search);
		}
		if (*str)
			res[i++] = *str;
		printf("RES %s\n", res);
		str++;
	}
	res[i] = 0;
	return (res);
}

char *search(char *s, int i)
{
	char	*res;
	int		j;

	i = 0;
	j = 1;
	while (s && s[i] && s[i] != '$' && s[i + 1])
		i++;
	if (s[i] && s[i + 1] && s[i + 1] == ' ')
		return (search(s, i));
	while (s && s[i] && s[i + j] && s[i + j] != ' ' && s[i + j] != '$')
		j++;
	res = malloc(sizeof(char) * (j + 1));
	j = 0;
	while (s && s[i] && s[i] != ' ')
		res[j++] = s[i++];
	res[j] = 0;
	printf("SEARCH %s\n", res);
	return (res);
}

int is_expandable(char *s, int i)
{
	int	sgl;
	int	dbl;
	int	j;

	sgl = 0;
	dbl = 0;
	j = -1;
	while (s && s[++j] && j < i)
	{
		((!sgl && !dbl && s[j] == '\"' && ++dbl) || (!dbl  && !sgl
		&& s[j] == '\'' && ++sgl) || (!sgl && dbl && s[j]== '\"' && ++dbl)
		|| (!dbl  && sgl && s[j] == '\'' && ++sgl));
	}
}
void	replace_words(t_shell *shell, t_token *tokens)
{
	char	*tmp;
	char	*tmp2;
	char	*tmp3;

	if (tokens->genre != ELEM_S_QUOTES && contain('$', tokens->s))
	{
		else
		{
			tmp = search(tokens->s, 0);
			if (ft_strncmp(tmp, "$?", 2))
				tmp2 = ft_itoa(g_err);
			tmp2 = get_replacement(tmp, shell);
			tmp3 = replace(tokens->s, tmp, tmp2);
			free(tokens->s);
			free(tmp);
			if (ft_strncmp(tmp, "$?", 2))
				free(tmp2);
			tokens->s = tmp3;
			printf("token %s\n", tmp3);
			continue ;
		}
	}

}
void	handle_history(t_shell *shell)
{
	//signal(SIGINT, handle);
	signal(SIGSEGV, handle);
	shell->line = readline("minishell> ");
	add_history(shell->line);
	shell->tokens = parse(shell->line);
	replace_words(shell, shell->tokens);
	while (shell->tokens)
	{
		printf("--------\n");
		printf("%s %s\n", ft_strtrim(shell->tokens->s, " "), get_token(shell->tokens->genre));
		//free(shell->tokens->s);
		shell->tokens = shell->tokens->next;
	}
	//system("leaks a.out");


}
void	handle(int sig)
{
	signal(SIGINT, handle);
	signal(SIGSEGV, handle);
	if (sig == SIGSEGV)
	{
		printf("\n\033[0;31mSEGFAULT BAAAAH T'ES NUL\033[0m\n");
		exit(0);
	}
	write(0, "\n", 1);
}

int	main(int ac, char **av, char **env)
{
	t_shell shell;
	shell.env = env;
	while (1)
	{
		handle_history(&shell);
	}
}