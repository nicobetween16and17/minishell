#ifndef MINISHL_H
# define MINISHL_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <dirent.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <limits.h>
# include <errno.h>
# include <signal.h>

typedef struct s_list
{
	char			*command;
	struct s_list	*next;
}	t_list;

typedef struct s_history
{
	t_list	commands;
}	t_history;
#endif