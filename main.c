#include "minishl.h"
t_list	*history;

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
void	handle(int signal)
{
	static int e;

	e++;
	write(0, "\n", 1);
	(void)signal;
	if (e > 3)
		exit(0);
}
void	check_line(char *line, int i)
{
	while (line[++i])
		if (line[i] == 4)
			exit(0);
}

int	main(int ac, char **av)
{
	int	fd;
	int fd_test;
	char cache[4096];

	history = NULL;
	fd_test = open("test", O_WRONLY);
	write(fd_test, "test", 4);
	fd = open("cache", O_RDWR | O_CREAT, 0666);
	printf("%d\n", fd);
	while (1)
	{
		signal(SIGINT, handle);
		add_front(&history, new_list(readline("minishell>")));
		write(fd, history->command, strlen(history->command));
		check_line(history->command, -1);
		write(fd, "\n", 1);
		printf("minishell>%s\n", history->command);
	}
}