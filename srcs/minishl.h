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
# define CMD 0
# define HDOC 1
# define TRUNC 2
# define APPEND 3
# define INPUT 4
# define PIPE 5

typedef struct s_utils
{
	int		i;
	int		cmd;
	int		last;
	t_list	*tokens;
	char	*tmp;
}	t_utils;

typedef struct s_token
{
	char	*filename;
	char	**cmds;
	int		type;
	struct s_token *next;
}t_token;

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
	int		i;
	int		pipe_failed;
}	t_pipe;

typedef struct s_shell
{
	char		*line;
	char		**env;
	int			infile;
	char		*heredoc;
	int			outfile;
	int			in;
	int			out;
	int 		exit;
	int			ret;
	int			no_exec;
	int			pipe_in;
	int			pipe_out;
	pid_t		pid;
	char		folie[10];
	int			parent;
	int			last;
	int			charge;
	t_token		*tokens;

}	t_shell;

typedef struct	s_sig
{
	int				s_int;
	int				s_quit;
	int				status;
	pid_t			pid;
}	t_sig;

t_sig g_signal;

int		contain(char c, char *s);
int		is_btwn_q(char *s, int i);
void	*xmalloc(size_t size);
int		is_charset(char c, char *charset);
int		cut_until(char *s, t_utils *utils, char *stop);
int		set_last(t_utils *utils, int i);
void	setup_cmd2(t_list *new, t_shell *sh);
void	setup_cmd(t_list *tokens, t_token **new, char *f, int i);
void	parse(char *s, t_shell *sh);
char	*sub(char *s, int start, int len);
void	exec_cmds(t_shell *shell, t_token *token);
int	ft_exit(char **params, t_shell *shell);
int	ft_export(char **params, t_shell *shell);
int	ft_unset(char **params, t_shell *shell);
int	ft_env(char **params, t_shell *shell);
int	ft_pwd(char **params, t_shell *shell);
int	ft_echo(char **params, t_shell *shell);
int	ft_cd(char **params, t_shell *shell);
void	env_in_alphabetic_order(char **envp);
int		here_doc(char *delimiter);
int		is_bi(char *cmd);
char	**env_init(const char **env);
char	*ft_strndup(char *s, int n);
t_token	*new_token(char *filename, char **cmds, int type);
int		token_size(t_token *lst);
t_token	*last_token(t_token *lst);
int		add_back(t_token **lst, t_token *new);
int		is_cmd(t_token *token);
void	*cmds_malloc(t_list *new);
int		next_token(t_list **token);
int		nb_cmd(t_token *lst);
void	ft_close(int fd);
void	reset_std(t_shell *sh);
void	close_fds(t_shell *sh);
void	reset_fds(t_shell *sh);
void	free_tab(char **tab, int i);
int		custom_pipe(t_shell *sh);
void	free_completed_tab(char **tab);
int		x_bi(char **cmd, int type, t_shell *sh);
char	*get_path(char *cmd, char *path);
void	redirect(t_shell *sh, char *f, int type);

#endif