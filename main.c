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
void	handle_parsing()
{
	char	*command;

	command = shell.current_cmd;
	if (!strncmp(command, "echo ", 5))
		handle_echo();
	if (!strncmp(command, "cat ", 4))
		handle_cat();
	if (!strncmp(command, "ls ", 3))
		handle_ls();
	if (!strncmp(command, "cd ", 3))
		handle_pwd();
	if (!strncmp(command, "pwd ", 4))
		handle_pwd();
	if (!strncmp(command, "export ", 7))
		handle_export();
	if (!strncmp(command, "env ", 4))
		handle_env();
	if (!strncmp(command, "unset ", 6))
		handle_unset();
	if (!strncmp(command, "exit ", 5))
		handle_exit();
	else
		printf("zsh: command not found: %s\n", shell.current_cmd);
}
void	handle_history()
{
	signal(SIGINT, handle);
	signal(SIGSEGV, handle);
	add_front(&shell.history, new_list(readline("\033[0;32mminishell>\033[0m")));
	//if (shell.current_cmd)
	//	free(shell.current_cmd);
	//printf("here\n");
	shell.current_cmd = strdup(shell.history->command);
	/*if (read(shell.fd_cache, shell.cache, 1) > 0)
		write(shell.fd_cache, "\f", 5);
	write(shell.fd_cache, shell.history->command, strlen(shell.history->command));
	write(shell.fd_cache, "\n", 1);
	//if (contain_pipe(shell.history->command))*/
	handle_parsing();
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