#include "../include/minishl.h"

t_token	*last(t_token *start)
{
	if (!start)
		return (start);
	while (start->next)
		start = start->next;
	return (start);
}

void	add_back(t_token **start, t_token *new)
{
	t_token	*tmp;

	tmp = last(*start);
	tmp->next = new;
}

char	*substr(char *s, int start, int end)
{
	char	*res;
	int		i;

	i = 0;
	if (start > end || end > ft_strlen(s) || start > ft_strlen(s))
		return (NULL);
	res = malloc(sizeof(char) * (end - start + 1));
	if (!res)
		return (NULL);
	while (start + i < end)
	{
		res[i] = (s + start)[i];
		i++;
	}
	res[end - start] = 0;
	return (res);
}

t_token	*new_token(char *s, t_type genre)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	new->s = s;
	new->genre = genre;
	new->next = NULL;
	return (new);
}
