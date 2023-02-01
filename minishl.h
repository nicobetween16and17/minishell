#ifndef MINISHL_H
# define MINISHL_H
# define HEREDOC .heredoc.temp
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

typedef struct s_utils
{
	int		i;
	int		cmd;
	int		last;
	t_list	*tokens;
	char	*tmp;
}	t_utils;

typedef struct s_utils2
{
	char	*sub;
	int		i;
	int		nbq;
	int		j;
	int		f;
}	t_utils2;

typedef struct s_pipe
{
	char	**crt;
	char	*cmd;
	pid_t	pid[400];
	int		nb_pid;
	int		len;
	int		n;
	int		fd[400][2];
	int		status;
}	t_pipe;

typedef struct s_shell
{
	char		*line;
	char		**env;
	int			infile;
	char		*heredoc;
	int			outfile;
	t_list		*cmd;

}	t_shell;

int g_err;
int		contain(char c, char *s);
int		is_btwn_q(char *s, int i);
void	*xmalloc(size_t size);
int		is_charset(char c, char *charset);
int		cut_until(char *s, t_utils *utils, char *stop);
int		set_last(t_utils *utils, int i);
void	setup_cmd2(t_list *new, t_shell *sh);
void	setup_cmd(t_list *tokens, t_shell *shell, char *f);
void	parse(char *s, t_shell *sh);
char	*sub(char *s, int len);
void	exec_cmds(t_shell *shell, t_list *cmds);
void	ft_exit(char **params, t_shell *shell);
void	ft_export(char **params, t_shell *shell);
void	ft_unset(char **params, t_shell *shell);
void	ft_env(char **params, t_shell *shell);
void	ft_pwd(char **params, t_shell *shell);
void	ft_echo(char **params, t_shell *shell);
void	ft_cd(char **params, t_shell *shell);
void	env_in_alphabetic_order(char **envp);
int		here_doc(char *delimiter);
int		is_builtin(char *cmd, char **params, t_shell *shell);
char	*get_path(char *cmd);
#endif