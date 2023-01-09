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
static void	set_files(t_token *t)
{
	int	is_filename;

	is_filename = 0;
	while (t)
	{
		if (is_filename)
		{
			t->genre = FILENAME;
			is_filename = 0;
		}
		if (t->genre == REDIR)
			is_filename = 1;
		t = t->next;
	}
}
t_token	*parse(char *s)
{
	t_parsing	p;

	init_parsing(&p);
	parsing(s, &p);
	set_files(p.t);
	if (p.quotes)
		return (NULL);
	return (p.t->next);
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