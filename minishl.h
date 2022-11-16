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
# include "libft/libft.h"

typedef struct s_request
{
	char			*cmd;
	char			*flags;
	char			**elements;
	struct s_list	*next;
}	t_request;

typedef struct s_parsing
{
	int			i;
	int			quotes;
	t_request	*requests;
	t_request	*head;
	char		*s;
	int			step;
	int			last_i;
}	t_parsing;
typedef struct s_cmd
{
	char	flags[53];
	char	alias[15];
	char	*content;
	int		redirection_fd;
	int		redirected;
	int		nb_flags;
}	t_cmd;

typedef struct s_shell
{
	char		*line;
	t_request	*request;
}	t_shell;

t_shell shell;
#endif