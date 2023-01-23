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
<<<<<<< HEAD
=======
	REDIR,
	CMD,
	ELEMENT,
	ELEM_S_QUOTES,
	ELEM_D_QUOTES,
	FLAGS,
	FILENAME
}	t_type;

enum
{
	EXIST,
	READ,
	WRITE
};

typedef struct s_token
{
	char			*s;
	t_type			genre;
	struct s_token	*next;
}	t_token;

typedef struct s_parsing
{
	t_token	*t;
	int		quotes;
>>>>>>> 755e4e3d0566aa50b82a2da88b990c80a8510290
	int		i;
	int		cmd;
	int		last;
	t_list	*tokens;
	char	*tmp;
}	t_utils;

typedef struct s_utils2
{
<<<<<<< HEAD
	char	*sub;
	int		i;
	int		nbq;
	int		j;
	int		f;
}	t_utils2;
=======
	char				*cmd;
	char				*flags;
	char				**elements;
	int					infile;
	int					outfile;
	char				*here_doc;
	struct s_request	*next;
	char				quote;
}	t_request;
>>>>>>> 755e4e3d0566aa50b82a2da88b990c80a8510290

typedef struct s_shell
{
	char		*line;
	char		**env;
	int			infile;
	char		*heredoc;
	int			outfile;
	t_list		*cmd;

}	t_shell;

<<<<<<< HEAD
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
=======
typedef struct	s_list_of_command
{
	t_request *cmd;
	struct s_list_of_command *next;
}	t_list_of_command;

t_shell shell;
t_token	*parse(char *s);
void	parsing();
char	*get_token(int n);
int		cut(t_parsing *p, char *s, t_type type);
int		add_quotes(t_parsing *p, char *s);
int		add_quote_content(t_parsing *p, char *s);
t_token	*last(t_token *start);
void	add_back(t_token **start, t_token *new);
char	*substr(char *s, int start, int end);
t_token	*new_token(char *s, t_type genre);
>>>>>>> 755e4e3d0566aa50b82a2da88b990c80a8510290
#endif