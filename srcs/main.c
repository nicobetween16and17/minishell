#include "minishl.h"

void	handle(int signal);

int ft_strisnum(char *s)
{
	int	i;

	i = -1;
	while (s && s[++i])
		if (!ft_isdigit(s[i]))
			return (0);
	return (1);
}

int	ft_exit(char **params, t_shell *shell)
{
	shell->exit = 1;
	ft_putstr_fd("exit ", 2);
	ft_strlcpy(shell->folie, "💚", 5);
	if (params[1])
		ft_strlcpy(shell->folie, "❤️", 5);
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
		ft_putendl_fd(": numeric argument required", 2);
	}
	else if (params[1])
		shell->ret = ft_atoi(params[1]);
	else
		shell->ret = 0;
	return (0);
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
/*void	handle_cmd(t_shell *shell)
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
}*/
void	handle_history(t_shell *shell)
{
	//signal(SIGINT, handle);
	//static int loop;

	//signal(SIGSEGV, handle);
	//int pid;
	//pid = getpid();
	//char *line;
	//line = ft_strjoin("lsof -p ", ft_itoa(pid));
	//printf("cmd %s\n", line);
	//system(line);
	shell->line = readline("minishell> ");
	//if (loop > 0)
	//	exit(0);
	//if (!shell->line)
	//{
	//	loop++;
	//	return ;
	//}
	printf("1 line : [%s]\n", shell->line);
	add_history(shell->line);
	replace_words(shell, -1, 0);
	parse(shell->line, shell);
	//shell->cmd = shell->cmd->next;
	//handle_cmd(shell);
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
void	s_int(int value)
{
	(void)value;
	if (g_signal.pid == 0)
	{
		ft_putstr_fd("\b\b  ", 2);
		ft_putstr_fd("\n", 2);
		ft_putstr_fd("\033[0;32m❌ minishell > \033[0m", 2);
		g_signal.status = 1;
	}
	else
	{
		ft_putstr_fd("\n", 2);
		g_signal.status = 130;
	}
	g_signal.s_int = 1;
}

void	s_quit(int value)
{
	char	*nbr;

	nbr = ft_itoa(value);
	if (g_signal.pid != 0)
	{
		ft_putstr_fd("Quit: ", 2);
		ft_putendl_fd(nbr, 2);
		g_signal.status = 131;
		g_signal.s_quit = 1;
	}
	else
		ft_putstr_fd("\b\b  \b\b", 2);
	free(nbr);
	nbr = NULL;
}

void	init_signal(void)
{
	g_signal.s_int = 0;
	g_signal.s_quit = 0;
	g_signal.pid = 0;
	g_signal.status = 0;
}
int error_open(char *file, t_shell *sh)
{
	sh->ret = 1;
	sh->no_exec = 1;
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(file, 2);
	ft_putendl_fd(": No such file or directory", 2);
	return (1);
}
void redirect(t_shell *sh, char *f, int type)
{
	if (type == HDOC || type == INPUT)
	{
		ft_close(sh->infile);
		if (type == HDOC)
			sh->infile = open(".heredoc.tmp", O_RDONLY);
		else
			sh->infile = open(f, O_RDONLY);
		if (sh->infile == -1 && error_open(f, sh))
			return ;
		dup2(sh->infile, 0);
		return;
	}
	ft_close(sh->outfile);
	if (type == APPEND)
		sh->outfile = open(f, O_CREAT | O_WRONLY | O_APPEND, 0700);
	else if (type == TRUNC)
		sh->outfile = open(f, O_CREAT | O_WRONLY | O_TRUNC, 0700);
	dup2(sh->outfile, 1);
}

int error_msg(char *path)
{
	DIR	*folder;
	int	fd;
	int	ret;

	fd = open(path, O_WRONLY);
	folder = opendir(path);
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(path, 2);
	if (ft_strchr(path, '/') == NULL)
		ft_putendl_fd(": command not found", 2);
	else if (fd == -1 && folder == NULL)
		ft_putendl_fd(": No such file or directory", 2);
	else if (fd == -1 && folder != NULL)
		ft_putendl_fd(": is a directory", 2);
	else if (fd != -1 && folder == NULL)
		ft_putendl_fd(": Permission denied", 2);
	if (ft_strchr(path, '/') == NULL || (fd == -1 && folder == NULL))
		ret = 127;
	else
		ret = 126;
	if (folder)
		closedir(folder);
	ft_close(fd);
	return (ret);
}

int	magic_box(char *path, char **args, t_shell *sh)
{
	int		ret;

	ret = 0;
	g_signal.pid = fork();
	if (g_signal.pid == 0)
	{
		if (ft_strchr(path, '/') != NULL)
			execve(path, args, sh->env);
		ret = error_msg(path);
		exit(ret);
	}
	else
		waitpid(g_signal.pid, &ret, 0);
	if (g_signal.s_int == 1 || g_signal.s_quit == 1)
		return (g_signal.status);
	ret = (ret == 32256 || ret == 32512) ? ret / 256 : ret;
	return (ret);
}

int	x_ve(char **cmds, t_shell *sh)
{
	int i;
	char *path;
	int ret;

	ret = 127;
	i = 0;
	while (sh->env && sh->env[i] && ft_strncmp("PATH=", sh->env[i], 5))
		i++;
	if (!sh->env[i] || !cmds || !cmds[0])
		return (1);
	path = get_path(cmds[0], sh->env[i] + 5);
	printf("path : %s\n", path);
	if (path)
		ret = magic_box(path, cmds, sh);
	else
		ret = magic_box(cmds[0], cmds, sh);
	free(path);
	return (ret);
}
void	exec_cmd(t_shell *sh, t_token *token)
{
	int		i;

	if (sh->charge == 0)
		return ;
	i = 0;
	if (token->cmds && ft_strncmp(token->cmds[0], "exit", 5) == 0)
		ft_exit(token->cmds, sh);
	else if (token->cmds && !x_bi(token->cmds, is_bi(token->cmds[0]), sh))
		sh->ret = x_ve(token->cmds, sh);
	ft_close(sh->pipe_in);
	ft_close(sh->pipe_out);
	sh->pipe_in = -1;
	sh->pipe_out = -1;
	sh->charge = 0;
}

char *type(int genre)
{
	if (genre == CMD)
		return ("CMD");
	if (genre == HDOC)
		return ("HDOC");
	if (genre == INPUT)
		return ("INPUT");
	if (genre == TRUNC)
		return ("TRUNC");
	if (genre == APPEND)
		return ("APPEND");
	if (genre == PIPE)
		return ("PIPE");
	return ("OTHER");

}
void	exec_plus_redirect(t_shell *sh, t_token *token)
{
	int	pipe;

	printf("type %s\n", type(token->type));
	pipe = 0;
	if (token->type != CMD)
		redirect(sh, token->filename, token->type);
	else
	{
		pipe = custom_pipe(sh);
		if (!pipe && !sh->no_exec)
			exec_cmd(sh, token);
	}
}

void	free_token(t_token *current)
{
	if (current->cmds == CMD)
		free_completed_tab(current->cmds);
	else
		free(current->filename);
	current->cmds = NULL;
	current->filename = NULL;
}

void	minishell(t_shell *sh)
{
	t_token	*token;
	int		status;

	token = sh->tokens;
	while (sh->exit == 0 && token)
	{
		sh->charge = 1;
		sh->parent = 1;
		sh->last = 1;
		exec_plus_redirect(sh, token);
		reset_std(sh);
		close_fds(sh);
		reset_fds(sh);
		waitpid(-1, &status, 0);
		status = WEXITSTATUS(status);
		if (sh->ret)
			sh->ret = status;
		/*if (!sh->parent)
		{
			free_token(sh->tokens);
			exit(sh->ret);
		}*/
		sh->no_exec = 0;
		token = token->next;
	}
}
void	checkline(t_shell *shell)
{
	char	*line;

	signal(SIGINT, &s_int);
	signal(SIGQUIT, &s_quit);
	if (shell->ret)
		ft_putstr_fd("❌ ", 2);
	else
		ft_putstr_fd("✔️ ", 2);
	line = readline("\033[0;32mminishell> \033[0m");
	if (!line)
	{
		ft_putstr_fd("\nline_exit", 2);
		exit(shell->ret);
	}
	else
	{
		if (g_signal.s_int == 1)
			shell->ret = g_signal.status;
		if (is_expandable(line, ft_strlen(line), 1))
			return;
		shell->line = line;
		add_history(line);
		replace_words(shell, -1, 0);
		parse(shell->line, shell);
		shell->tokens = shell->tokens->next;
		free(line);
		line = NULL;
	}
}
void display2(t_token *t)
{
	int i;

	i = 1;
	while (t)
	{
		printf("token %d: %s\n", i++, type(t->type));
		t = t->next;
	}
}
int	main(int ac, char **av, char **env)
{
	t_shell shell;
	int		status;

	(void)ac;
	(void)av;
	shell.tokens = NULL;
	shell.in = dup(0);
	shell.out = dup(1);
	shell.exit = 0;
	shell.ret = 0;
	shell.no_exec = 0;
	shell.env = env_init((const char **)env);
	init_signal();
	while (!shell.exit)
	{
		shell.infile = 0;
		shell.outfile = 1;
		checkline(&shell);
		display2(shell.tokens);
		exec_cmds(&shell, shell.tokens);
		close_fds(&shell);
		reset_std(&shell);
		reset_fds(&shell);
		waitpid(-1, &status, 0);
		status = WEXITSTATUS(status);
		if (shell.ret)
			shell.ret = status;
		//printf("yo\n");
		//minishell(&shell);
	}
	return (0);
}