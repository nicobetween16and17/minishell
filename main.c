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
int	is_alpha(char c)
{
	return ((c <= 90 && c >= 65) || (c <= 126 && c >= 97));
}

void	handle_history()
{
	//signal(SIGINT, handle);
	signal(SIGSEGV, handle);
	shell.line = readline("minishell> ");
	add_history(shell.line);
	//parsing();
	int i = fork();
	if (i == 0)
		execve("/bin/bash", &shell.line, shell.env);
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