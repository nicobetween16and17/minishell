/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishl.h                                           :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: niespana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 21:12:12 by niespana          #+#    #+#             */
/*   Updated: 2023/01/19 21:12:13 by niespana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHL_H
# define MINISHL_H
# define HEREDOC ".heredoc.temp"
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
# define RIGHT 6
# define LEFT 7
# define ABS(Value)	Value < 0 ? -Value : Value

typedef struct s_utils
{
	int		i;
	int		cmd;
	int		last;
	t_list	*tokens;
	char	*tmp;
}	t_utils;

typedef struct s_err
{
	int		rep;
	int		err;
	char	c;
}t_err;

typedef struct s_token
{
	char			*filename;
	char			**cmds;
	int				type;
	struct s_token	*next;
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
	t_token	*current;
}	t_pipe;

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}t_env;

typedef struct s_shell
{
	char		*line;
	char		*tmp;
	char		**env;
	int			infile;
	int			outfile;
	int			dir;
	int			in;
	int			out;
	int			exit;
	int			ret;
	char		folie[10];
	int			last;
	t_env		*env_lst;
	t_token		*tokens;

}	t_shell;

typedef struct s_sig
{
	int		s_int;
	int		s_quit;
	int		status;
	pid_t	pid;
	char	str_status[10];
}	t_sig;

t_sig	g_signal;

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
int		ft_exit(char **params, t_shell *shell);
int		ft_export(char **params, t_shell *shell);
int		ft_unset(char **params, t_shell *shell);
int		ft_env(char **params, t_shell *shell);
int		ft_pwd(char **params, t_shell *shell);
int		ft_echo(char **params, t_shell *shell);
int		ft_cd(char **params, t_shell *shell);
void	env_in_alphabetic_order(t_env *env);
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
int		ft_strisnum(char *s);
void	free_completed_tab(char **tab);
int		x_bi(char **cmd, int type, t_shell *sh);
char	*get_path(char *cmd, char *path);
void	redirect(t_shell *sh, char *f, int type);
int		ft_exit(char **params, t_shell *shell);
int		find(char *env_line, char *to_find);
int		contain(char c, char *s);
char	*get_env(char *s, char **env);
char	*empty_freeable_string(void);
char	*replace(char *str, char *start, char *end, char *replace);
int		is_expandable(char *s, int i, int open);
void	replace_words(t_shell *shell, int i, int j);
int		error_open(char *file, t_shell *sh);
void	redirect(t_shell *sh, char *f, int type);
void	init_signal(void);
void	s_quit(int value);
void	s_int(int value);
void	set_redir(char *f, t_list *tokens, t_token **new);
char	*name_env_var(char *s);
int		check_arg(char *s);
void	init_pipe(t_pipe *pipex, t_token *cmds);
int		x_bi(char **cmd, int type, t_shell *sh);
int		is_bi(char *cmd);
int		nb_pipe(t_token *t);
int		only_redir(char *s);
char	*get_env_line(char **env, char *env_line);
t_env	*new_env(char *name, char *value);
int		env_size(t_env *lst);
t_env	*last_env(t_env *lst);
int		add_env(t_env **lst, t_env *new);
char	*get_env_value(t_env *env_lst, char *s);
int		remove_env(t_shell *sh, char *s);
int		change_env(t_env *env, char *s);
int		get_env_size(t_env *env);
char	**get_env_tab(t_env *env);
void	free_env_lst(t_env *env);
t_env	*init_lst(char **tab);
char	*get_side(int side, char *s);
int		check_forbidden(char *s, t_shell *sh);
#endif