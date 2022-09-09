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

typedef struct s_shell
{
	t_list	*history;
	int		fd_cache;
	char	*output;
	int		fd_redir;
	char	flag;
	char	*current_cmd;
}	t_shell;

void	handle_exit(void);
void	handle_unset(void);
void	handle_env(void);
void	handle_export(void);
void	handle_pwd(void);
void	handle_pwd(void);
void	handle_ls(void);
void	handle_cat(void);
void	handle_echo(void);
void	handle_parsing(void);
t_shell shell;
#endif