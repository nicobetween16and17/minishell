#include "minishl.h"

void	handle(int signal);

void	add_front(t_list **body, t_list *limb)
{
	limb->next = *body;
	*body = limb;
}

t_list	*new_list(char *line)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	new->next = NULL;
	new->command = line;
	return (new);
}
void	handle_alias()
{
	char	*command;

	if (!strncmp(command, "echo ", 5))
		shell.current_cmd.alias = "echo";
	else if (!strncmp(command, "cat ", 4))
		shell.current_cmd.alias = "cat";
	else if (!strncmp(command, "ls ", 3))
		shell.current_cmd.alias = "ls";
	else if (!strncmp(command, "cd ", 3))
		shell.current_cmd.alias = "cd";
	else if (!strncmp(command, "pwd ", 4))
		shell.current_cmd.alias = "pwd";
	else if (!strncmp(command, "export ", 7))
		shell.current_cmd.alias = "export";
	else if (!strncmp(command, "env ", 4))
		shell.current_cmd.alias = "env";
	else if (!strncmp(command, "unset ", 6))
		shell.current_cmd.alias = "unset";
	else if (!strncmp(command, "exit ", 5))
		shell.current_cmd.alias = "exit";;
}

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
int	is_alpha(char c)
{
	return ((c <= 90 && c >= 65) || (c <= 126 && c >= 97));
}

void	handle_flags()
{
	shell.current_cmd.nb_flags = 0;
	shell.history->command += (strlen(shell.current_cmd.alias) + 1);
	shell.increment += (strlen(shell.current_cmd.alias) + 1);
	while (*shell.history->command == ' ' && shell.increment++)
		shell.history->command++;
	if (shell.history->command && *shell.history->command == '-' && shell.increment++)
		shell.history->command++;
	while (shell.history->command && *shell.history->command != ' ' && shell.increment++)
	{
		if (!contain(*shell.history->command, flags) && is_alpha(*shell.history->command))
			shell.current_cmd.flags[shell.current_cmd.nb_flags++] = *shell.history->command;
	}
	shell.current_cmd.flags[shell.current_cmd.nb_flags + 1] = 0;
}

void	handle_output()
{
	if (!strncmp(command, "echo", 5))
		handle_echo();
	else if (!strncmp(command, "cat", 3))
		handle_cat();
	else if (!strncmp(command, "ls", 2))
		handle_ls();
	else if (!strncmp(command, "cd", 2))
		handle_cd();
	else if (!strncmp(command, "pwd", 3))
		handle_pwd();
	else if (!strncmp(command, "export", 6))
		handle_export();
	else if (!strncmp(command, "env", 3))
		handle_env();
	else if (!strncmp(command, "unset", 5))
		handle_unset();
	else if (!strncmp(command, "exit", 4))
		handle_exit();
}

void	handle_cmd()
{
	handle_alias();
	if (shell.current_cmd.alias[0] != 0)
	{
		handle_flags();
		shell.content = shell.history->command;
		handle_output();
		handle_redirection();
		if (contain('|', shell.history->command))
			handle_cmd();
	}

}
void	handle_history()
{
	signal(SIGINT, handle);
	signal(SIGSEGV, handle);
	add_front(&shell.history, new_list(readline("\033[0;32mminishell>\033[0m")));
	shell.current_cmd = strdup(shell.history->command);
	handle_cmd();

}
void	handle(int sig)
{
	signal(SIGINT, handle);
	signal(SIGSEGV, handle);
	if (sig == SIGSEGV)
		exit(0);
	write(0, "\n", 1);
	handle_history();
}

int	main(int ac, char **av)
{
	int	fd;
	int	fd_test;

	shell.flag = 0;
	shell.history = NULL;
	fd_test = open("test", O_WRONLY);
	write(fd_test, "test", 4);
	fd = open("cache", O_RDWR | O_CREAT, 0666);
	shell.fd_cache = fd;
	while (1)
	{
		handle_history();
	}
}