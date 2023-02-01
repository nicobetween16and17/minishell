#include "minishl.h"

void	handle(int signal);
void	ft_exit(char **params, t_shell *shell)
{
	(void)params;
	(void)shell;
	ft_putstr_fd("\nexit\n", 1);
	exit(g_err);
}
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
	int	i;

	i = 0;
	while (env_line[i] && ft_strncmp(env_line + i, to_find, ft_strlen(to_find)))
		i++;
	return (env_line[i]);
}

char	*get_env(char *s, char **env)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (env[i] && !find(env[i], s))
		i++;
	if (!env[i])
		return ("");
	while (env[i][j] != '=')
		++j;
	j++;
	return (env[i] + j);
}

char	*empty_freeable_string()
{
	char *str;

	str = malloc(1);
	str[0] = 0;
	return (str);
}

char	*replace(char *str, char *start, char *end, char *replace)
{
	char	*res;
	int		i;

	i = 0;
	if ((end - start) <= 1)
		return (empty_freeable_string());
	res = malloc(sizeof(char) * (ft_strlen(str)
								 - (end - start) + ft_strlen(replace) + 1));
	while (str && *str)
	{
		if (str == start)
		{
			while (replace && *replace)
				res[i++] = *(replace++);
			str += (end - start);
		}
		if (*str)
			res[i++] = *str;
		str++;
	}
	res[i] = 0;
	return (res);
}


int	is_expandable(char *s, int i, int open)
{
	int	sgl;
	int	dbl;
	int	j;

	sgl = 0;
	dbl = 0;
	j = -1;
	while (s && s[++j] && j < i)
	{
		((!sgl && !dbl && s[j] == '\"' && ++dbl) || (!dbl && !sgl\
		&& s[j] == '\'' && ++sgl) || (!sgl && dbl && s[j] == '\"'\
		&& dbl--) || (!dbl && sgl && s[j] == '\'' && sgl--));\
	}
	if (open)
		return (sgl || dbl);
	return (!sgl);
}

void	replace_words(t_shell *shell, int i, int j)
{
	char *tmp2;
	char *tmp;

	while (shell->line && shell->line[++i])
	{
		if (shell->line[i] == '$' && is_expandable(shell->line, i, 0)
			&& shell->line[i + 1] != '/' && shell->line[i + 1] != '$'
			&& shell->line[i + 1] != ' ' && shell->line[i + 1] != '.'
			&& shell->line[i + 1] != '\'' && shell->line[i + 1] != '\"'
			&& shell->line[i + 1] != '|')
		{
			tmp2 = shell->line;
			j = i + 1;
			while (shell->line[j] != '/' && shell->line[j] != ' '
				   && shell->line[j] != '.' && shell->line[j] != '\''
				   && shell->line[j] != '\"' && shell->line[j] != '$'
				   && shell->line[j] != '|')
				j++;
			tmp = ft_substr(shell->line, i, j - i);
			shell->line = replace(shell->line, shell->line + i, \
			shell->line + j, get_env(tmp + 1, shell->env));
			free(tmp2);
			free(tmp);
		}
	}
}
void	handle_cmd(t_shell *shell)
{
	pid_t	pid;
	char	*cmd;

	if (ft_lstsize(shell->cmd) < 2)
	{
		if (!is_builtin(*(char **)shell->cmd->content, (char **)shell->cmd->content, shell))
		{
			cmd = get_path(*(char **)(shell->cmd->content));
			pid = fork();
			if (!pid)
				execve(cmd, (char **)shell->cmd->content, shell->env);
			free(cmd);
			wait(&pid);
		}
	}
	else
		exec_cmds(shell, shell->cmd);
}
void	handle_history(t_shell *shell)
{
	//signal(SIGINT, handle);


	//signal(SIGSEGV, handle);
	shell->line = readline("minishell> ");
	//printf("1\n");
	add_history(shell->line);
	//printf("2\n");
	replace_words(shell, -1, 0);
	//printf("3\n");
	parse(shell->line, shell);
	//printf("4\n");
	shell->cmd = shell->cmd->next;
	handle_cmd(shell);
	//printf("stop\n");
	//system("leaks a.out");


}
void	handle(int sig)
{
	signal(SIGINT, handle);
	signal(SIGSEGV, handle);
	if (sig == SIGSEGV)
	{
		printf("segfaulf\n");
		exit(0);
	}
	write(0, "\n", 1);
}

int	main(int ac, char **av, char **env)
{
	t_shell shell;

	(void)ac;
	(void)av;
	shell.env = env;
	shell.cmd = NULL;
	while (1)
	{
		shell.infile = 0;
		shell.outfile = 1;
		handle_history(&shell);
	}
	return (0);
}