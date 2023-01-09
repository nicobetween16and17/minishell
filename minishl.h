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

typedef enum e_type
{
	REDIR,
	CMD,
	ELEMENT,
	ELEM_S_QUOTES,
	ELEM_D_QUOTES,
	FLAGS,
	FILENAME
}	t_type;

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
	int		i;
	int		last_i;
	char	quotes_type;
}	t_parsing;

typedef struct s_request
{
	char				*cmd;
	char				*flags;
	char				**elements;
	struct s_request	*next;
}	t_request;

typedef struct s_shell
{
	char		*line;
	char		**env;
	t_env		*lst_env;
	t_token		*tokens;

}	t_shell;

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
#endif