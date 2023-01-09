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

void	replace(char *str, char *search, char *replace)
{
	char	*ptr;
	int		search_len;
	int		replace_len;

	ptr = str;
	search_len = ft_strlen(search);
	replace_len = ft_strlen(replace);
	ptr = ft_strnstr(ptr, search, ft_strlen(ptr));
	while (ptr != NULL)
	{
		ft_memmove(ptr + replace_len, ptr + search_len,
				   ft_strlen(ptr + search_len) + 1);
		ft_memcpy(ptr, replace, replace_len);
		ptr += replace_len;
		ptr = ft_strnstr(ptr, search, ft_strlen(ptr));
	}
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

void	replace_words(t_shell *shell)
{
	char	*tmp;
	char	*tmp2;

	while (shell->tokens)
	{
		if (shell->tokens->genre != ELEM_S_QUOTES)
		{
			if (shell->tokens->genre != ELEM_D_QUOTES)
			{
				tmp = get_replacement(shell->tokens->s + 1);
				free(shell->tokens->s);
				shell->tokens->s = tmp;
			}
			else if (contain('$', shell->tokens->s))
			{
				tmp = search(shell->tokens->s);
				tmp2 = get_replacement(tmp + 1);
				printf("string tot [%s]\nsearch [%s]\nreplacement [%s]\n", shell->tokens->s, tmp, tmp2);
				replace(shell->tokens->s, tmp, tmp2);
				printf("string tot [%s]\nsearch [%s]\nreplacement [%s]\n", shell->tokens->s, tmp, tmp2);
				continue ;
			}
		}
		shell->tokens = shell->tokens->next;
	}
}
void	handle_history()
{
	t_token *tmp;

	signal(SIGSEGV, handle);
	shell.line = readline("minishell> ");
	add_history(shell.line);
	shell.tokens = parse(shell.line);
	tmp = shell.tokens;
	replace_words(&shell);
	shell.tokens = tmp;
	while (shell.tokens)
	{
		printf("--------\n");
		printf("%s %s\n", ft_strtrim(shell.tokens->s, " "), get_token(shell.tokens->genre));
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
t_env	*last_env(t_env *start)
{
	if (!start)
		return (start);
	while (start->next)
		start = start->next;
	return (start);
}
void	add_back_env(t_env **start, t_env *new)
{
	t_env	*tmp;

	tmp = last_env(*start);
	tmp->next = new;
}

void set_lst_env(t_env *lst_env, char **env, int i)
{
	t_env	current;
	char	**split;

	while (env && env[++i])
	{
		split = ft_split(env[i], '=');
		printf("[%s]\n[%s]\n", split[0], split[1]);
		current.next = NULL;
		current.name = split[0];
		current.value = split[1];
		if (!lst_env)
			lst_env = &current;
		else
			add_back_env(&lst_env, &current);
		free(split);
	}
}
int	main(int ac, char **av, char **env)
{
	t_env list;

	shell.env = env;
	set_lst_env(&list, env, -1);
	shell.lst_env = &list;
	exit(0);
	int i = -1;
	while (env && env[++i])
		printf("%s\n", env[i]);
	while (shell.lst_env)
	{
		printf("name: %s\nvalue: %s\n", shell.lst_env->name, shell.lst_env->value);
		shell.lst_env = shell.lst_env->next;
	}
	exit(0);
	while (1)
	{
		handle_history();
	}
}