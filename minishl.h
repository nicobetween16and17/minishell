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

typedef struct s_requests
{
	char				flags[56];
	char				alias[15];
	char				*content;
	int					out;
	int					in;
	struct s_requests	*next;
}	t_request;

typedef struct s_shell
{
	t_list		*history;
	int			fd_cache;
	char		*output;
	t_request	*request;
}	t_shell;

t_shell shell;
#endif