#include "minishl.h"

void	init_parsing(t_parsing *p)
{
	p->t = new_token("", ELEMENT);
	p->quotes_type = 0;
	p->last_i = 0;
	p->i = -1;
	p->quotes = 0;
}

void	parsing(char *s, t_parsing *p)
{
	while (s[++p->i])
	{
		if (!p->quotes)
		{
			if ((s[p->i] == '>' || s[p->i] == '<') && cut(p, s, REDIR))
				continue ;
			if ((s[p->i] == '\"' || s[p->i] == '\'') && add_quotes(p, s))
				continue ;
			if ((p->last_i == 0 || (s[p->i] == '|' && ++p->i))
				&& cut(p, s, CMD))
				continue ;
			if (!last(p->t)->genre && cut(p, s, ELEMENT))
				continue ;
			if (s[p->i] == '-' && cut(p, s, FLAGS))
				continue ;
			if (s[p->i] != ' ' && s[p->i] != '\'' && s[p->i] != '\"'
				&& s[p->i] != '>' && s[p->i] != '<' && s[p->i] != '|'
				&& cut(p, s, ELEMENT))
				continue ;
		}
		if (p->quotes)
			add_quote_content(p, s);
	}
}

void	setup_file(t_shell *sh, char *type, char *filename)
{
	int	file;


	if (!ft_strncmp(type, "<", 2))
	{
		file = open(filename, O_RDWR;
		if (file == -1)
			printf("%s: permission denied\n", filename);
	}
	else if (!ft_strncmp(type, "<<", 3))
		;//TODO HERDEDOC
	else if (!ft_strncmp(type, ">", 2))
		file = open(filename, O_RDWR | O_CREAT | O_APPEND, 0644);
	else if (!ft_strncmp(type, ">>", 3))
		file = open(filename, O_RDWR | O_APPEND | O_CREAT, 0644);;
}
static void	set_files(t_token *t, t_shell *sh)
{
	int		is_filename;
	char	*redir;

	is_filename = 0;
	while (t)
	{
		if (is_filename)
		{
			t->genre = FILENAME;
			setup_file(sh, redir, t->s);
			is_filename = 0;
		}
		if (t->genre == REDIR)
		{
			is_filename = 1;
			redir = t->s;
		}
		t = t->next;
	}
}

void	set_cmds(t_shell *sh)//TODO current is supposed to remember the pointer to the start of the current cmd and the while line 98 must start at this pointer
{
	char		**cmds;
	int			i;
	static int	cmd;
	int			j;
	t_token	*head;
	t_token *current;
	i = 0;
	head = sh->tokens;
	while (sh->tokens)
	{
		if (cmd && sh->tokens->genre == CMD)
		{
			current = sh->tokens;
			j = 0;
			sh->tokens = head;
			cmds = xmalloc(sizeof(char **) * (cmd + i + 1));
			while (sh->tokens && i--)
			{
				if (sh->tokens->genre == CMD || sh->tokens->genre == ELEMENT
					|| sh->tokens->genre == ELEM_D_QUOTES
					|| sh->tokens->genre == ELEM_S_QUOTES)
					cmds[j++] = sh->tokens->s;
				sh->tokens = sh->tokens->next;
			}
			if (sh->cmd == NULL)
				sh->cmd = ft_lstnew(cmds);
			else
				ft_lstadd_back(&sh->cmd, ft_lstnew(cmds));
			free(cmds);
			cmd--;
		}
		if (!cmd && sh->tokens->genre == CMD)
			cmd++;
		if (sh->tokens->genre == CMD || sh->tokens->genre == ELEMENT
			|| sh->tokens->genre == ELEM_D_QUOTES
			|| sh->tokens->genre == ELEM_S_QUOTES)
			i++;
		sh->tokens = sh->tokens->next;
	}
	sh->tokens = head;
}

t_cmd	*parse(char *s, t_shell *shell)
{
	t_parsing	p;

	init_parsing(&p);
	parsing(s, &p);
	set_files(p.t, shell);
	shell->tokens = p.t->next
	set_cmds(&shell);
	if (p.quotes)
		return (NULL);
	return (shell->cmd);
}

char	*add_space(char *s)
{
	char	*res;
	int		i;

	i = 0;
	res = malloc(sizeof(char) * (ft_strlen(s) + 2));
	if (!res)
		return (NULL);
	while (s && *s)
		res[i++] = *s++;
	res[i++] = ' ';
	res[i] = 0;
	return (res);
}