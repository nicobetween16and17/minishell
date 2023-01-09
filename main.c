#include "minishl.h"

void	handle(int signal);

int	contain(char c, char *s)
{
	int	i;

	i = -1;
	while (s && s[++i])
	{
		if (s[i] == c)
			return (1);
	}
	return (0);
}

char *get_replacement(char *s1)
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
	return (getenv(s2));
}

char	*replace(char *str, char *search, char *replace)
{
	char	*res;
	char	*start;
	int		i;

	i = 0;
	start = ft_strnstr(str, search, ft_strlen(str));
	res = malloc(sizeof(char) * (ft_strlen(str) - ft_strlen(search) + ft_strlen(replace) + 1));
	while (str && *str)
	{
		res[i++] = *str;
		if (str == start)
		{
			while (replace && *replace)
				res[i++] = *(replace++);
			str += ft_strlen(search) - 1;
		}
		str++;
	}
	return (str);
}

char *search(char *s)
{
	char	*res;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (s && s[i] && s[i] != '$')
		i++;
	while (s && s[i + j] && s[i + j] != ' ')
		j++;
	res = malloc(sizeof(char) * (j + 1));
	j = 0;
	while (s && s[i] && s[i] != ' ')
		res[j++] = s[i++];
	res[j] = 0;
	return (res);
}

void	replace_words(t_shell *shell, t_token *tokens)
{
	char	*tmp;
	char	*tmp2;
	char	*tmp3;
	while (tokens)
	{
		if (tokens->genre != ELEM_S_QUOTES)
		{
			if (tokens->genre != ELEM_D_QUOTES)
			{
				tmp = get_replacement(tokens->s + 1);
				free(tokens->s);
				shell->tokens->s = tmp;
			}
			else if (contain('$', tokens->s))
			{
				tmp = search(tokens->s);
				tmp2 = get_replacement(tmp + 1);
				printf("string tot [%s]\nsearch [%s]\nreplacement [%s]\n", tokens->s, tmp, tmp2);
				tmp3=replace(tokens->s, tmp, tmp2);
				free(tokens->s);
				tokens->s = tmp3;
				printf("string tot [%s]\nsearch [%s]\nreplacement [%s]\n", tokens->s, tmp, tmp2);
				continue ;
			}
		}
		tokens = tokens->next;
	}
}
void	handle_history()
{
	signal(SIGSEGV, handle);
	shell.line = readline("minishell> ");
	add_history(shell.line);
	shell.tokens = parse(shell.line);
	replace_words(&shell, shell.tokens);
	while (shell.tokens)
	{
		printf("--------\n");
		printf("%s %s\n", ft_strtrim(shell.tokens->s, " "), get_token(shell.tokens->genre));
		free(shell.tokens.s);
		shell.tokens = shell.tokens->next;
	}

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
	handle_history();
}

int	main(int ac, char **av, char **env)
{
	shell.env = env;
	while (1)
	{
		handle_history();
	}
}