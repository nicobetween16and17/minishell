#include "../include/minishl.h"

int	check_here_doc_access(int fd, char *file_name)
{
	if (fd < 0)
	{
		if (check_access_of_file(file_name, EXIST))
			return (1);
		if (check_access_of_file(file_name, WRITE))
			return (1);
	}
	return (0);
}

void	heredoc_handler(int n)
{
	if (n == SIGINT)
	{
		unlink(HEREDOC);
		exit(0);
	}
}

int here_doc(char *delimiter)
{
	char *buffer;
	int here_doc_file;
	int j;
	pid_t pid;
	j = 0;
	struct sigaction sa;

	sa.sa_handler = &heredoc_handler;
	sa.sa_flags = SA_RESTART;
	pid = fork();
	if (!pid)
	{
		sigaction(SIGINT, &sa, NULL);
		here_doc_file = open(HEREDOC, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (check_here_doc_access(here_doc_file, HEREDOC))
		{
			printf("on sooooort\n");
			exit(1);
		}
		while(1)
		{
			buffer = readline("> ");
			if (!ft_strncmp(buffer, delimiter, ft_strlen(buffer)) && ft_strlen(buffer) == ft_strlen(delimiter))
				break ;
			else
			{
				if (j)
					write(here_doc_file, "\n", 1);
				else
					j++;
				write(here_doc_file, buffer, ft_strlen(buffer));
			}
		}
		close(here_doc_file);
		exit(0);
	}
	else
		waitpid(pid, NULL, 0);
	here_doc_file = open(HEREDOC, O_RDONLY);
	return (here_doc_file);
}