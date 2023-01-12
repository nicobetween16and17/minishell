#include "minishl.h"

char	*get_token(int n)
{
	if (n == 0)
		return ("REDIR");
	else if (n == 1)
		return ("CMD");
	else if (n == 2)
		return ("ELEMENT");
	else if (n == 3)
		return ("ELEM_S_QUOTES");
	else if (n == 4)
		return ("ELEM_D_QUOTES");
	else if (n == 5)
		return ("FLAGS");
	else if (n == 6)
		return ("FILENAME");
	else
		return ("NONE");
}

int	cut(t_parsing *p, char *s, t_type type)
{
	char	c;

	c = s[p->i];
	p->last_i = p->i;
	while (s[p->i] && s[p->i] == ' ')
		p->i++;
	while (s[p->i] && s[p->i] != ' ' && s[p->i] != '>'
		   && s[p->i] != '<' && s[p->i] != '|')
		p->i++;
	if (c == '<' || c == '>')
		while (s[p->i] && (s[p->i] == '>' || s[p->i] == '<'))
			p->i++;
	add_back(&p->t, new_token((ft_substr(s, p->last_i, p->i)), type));
	p->last_i = p->i;
	if (s[p->i] == ' ')
		p->i--;
	return (1);
}

int	add_quotes(t_parsing *p, char *s)
{
	p->quotes++;
	p->quotes_type = s[p->i];
	return (1);
}

int	add_quote_content(t_parsing *p, char *s)
{
	p->last_i = p->i;
	while (s[p->i] && s[p->i] != p->quotes_type)
		p->i++;
	if (p->quotes_type == '\'')
		add_back(&p->t, new_token(substr(s, p->last_i, p->i), ELEM_S_QUOTES));
	else
		add_back(&p->t, new_token(substr(s, p->last_i, p->i), ELEM_D_QUOTES));
	if (s[p->i])
		p->quotes = 0;
	p->quotes_type = 0;
	return (1);
}