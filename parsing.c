#include "minishl.h"

void nb_quotes(char *s)
{
	int	nb_quotes;

	if (!s)
		s = shell.line
	nb_quotes = 0;
	while (s && *s)
		if (*s++ == '\"')
			nb_quotes++;
	return (nb_quotes);
}

void	set_index_quotes(int **index_quote, int i, int malloc_size)
{
	int *i_qs;
	int current_index;

	i_qs = malloc(sizeof(int) * (malloc_size + 1))
	current_index = 1;
	i_qs[0] = 0;
	while (shell.line && shell.line[i])
	{

	}
	*index_quote = i_qs;
}

int	array_size(char **arr)
{
	int	i;

	i = 0;
	while (arr && arr[i])
		i++;
	return (i);
}

void add_elements(char ***elements, char *s)
{

}
void parsing()
{
	t_parsing p;

	p.i = -1;
	p.s = shell.line;
	p.quotes = 0;
	p.requests = malloc(sizeof(t_request));
	while (p.s && p.s[++i])
	{
		if (s[p.i] == ' ' && !p.quotes)
		{
			if (p.step == 0)
			{
				p.step++;
				requests->cmd = ft_substr(p.s, 0, p.i);
				p.last_i == i + 1;
				continue;
			}
			if (p.step == 1 && s[p.i + 1] == '-')
			{
				p.step++;
				requests->cmd = ft_substr(p.s, 0, p.i);
				p.last_i == i + 1;
				continue;
			}
			else if (step == 1)
				step++;
			if (step == 2)
			{
				add_elements(&p.requests->elements, ft_substr(p.s, p.last_i, p.i));
				last_i == i;
				continue;
			}
		}
		if (!p.quotes && s[p.i] == '\"')
		{
			while (s[p.i] && s[p.i++] == '\"')
				p.quotes++;
			p.last_i = i;
		}
		if (p.quotes && s[p.i] == '\"')
		{
			add_elements(&p.requests->elements, ft_substr(p.last_i, p.i))
			while (s[p.i] && s[p.i++] == '\"' && p.quotes)
				p.quotes--;

		}
	}
}