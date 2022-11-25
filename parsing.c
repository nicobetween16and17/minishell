#include "minishl.h"
int	ft_arlen(char **array)
{
	int	i;

	i = 0;
	while (array && array[i])
		i++;
	return (i);
}

char	**add_elements(char **elements, char *s)
{
	char	**element;
	int		i;
	int		size;

	size = ft_arlen(elements) + 2;
	i = 0;
	element = malloc(sizeof(char *) * size);
	while (elements && elements[i])
	{
		element[i] = ft_strdup(elements[i]);
		i++;
	}
	element[i++] = ft_strdup(s);
	element[i] = NULL;
	i = -1;
	while (elements && elements[++i])
		free(elements[i]);
	printf("added elem %s\n", s);
	return (element);
}

void	display_request(t_request *start)
{
	int	i;

	printf("start display\n");
	while (start)
	{
		i = 0-1;
		printf("cmd\t:\t%s\nflags\t:\t%s\nelements\t:\t", start->cmd, start->flags);
		while (start->elements && start->elements[++i])
			printf("[%d.%s] ", i, start->elements[i]);
		printf("\n-----------------------\n");
		start = start->next;
	}
	printf("end diplay\n");
}
void parsing()
{
	t_parsing p;

	p.i = -1;
	p.s = ft_strtrim(shell.line, " ");
	p.quotes = 0;
	p.requests = malloc(sizeof(t_request));
	p.requests->next = NULL;
	p.head = p.requests;
	p.last_i = 0;
	p.requests->elements = NULL;
	while (p.s && p.s[++p.i])
	{
		//printf("%s\n", ft_substr(p.s, p.last_i, p.i - p.last_i));
		if (!p.quotes && (p.s[p.i] == ' ' || (!p.s[p.i + 1] && p.i++)))
		{
			if (p.step == 0)
			{
				printf("adding cmd %s\n", ft_substr(p.s, p.last_i, p.i- p.last_i));
				p.step++;
				p.requests->cmd = ft_substr(p.s, p.last_i, p.i- p.last_i);
				p.last_i = p.i + 1;
				if (p.s[p.i + 1] == '-')
					p.flag = 1;
				continue;
			}
			if (p.step == 1 && p.flag)
			{
				printf("adding flags\n");
				p.step++;
				p.requests->flags = ft_substr(p.s, p.last_i, p.i - p.last_i);
				printf("flag is %s\n", p.requests->flags);
				p.last_i = p.i + 1;
				p.flag = 0;
				continue;
			}
			else if (p.step == 1)
				p.step++;
			if (p.step == 2)
			{
				printf("adding element\n");
				p.requests->elements = add_elements(p.requests->elements, ft_substr(p.s, p.last_i, p.i - p.last_i));
				p.last_i = p.i + 1;
				continue;
			}
		}
		if (!p.quotes && p.s[p.i] == '\"')
		{
			printf("FOUND QUOTES\n");
			p.quotes++;
			p.last_i = p.i;
		}
		if (p.quotes && p.s[p.i] == '\"')
		{
			printf("FOUND END QUOTES\n");
			p.requests->elements = add_elements(p.requests->elements, ft_substr(p.s, p.last_i, p.i - p.last_i));
			p.last_i = p.i + 1;
			p.quotes--;
		}
		if (!p.quotes && p.s[p.i] == '|')
		{
			p.requests->next = malloc(sizeof(t_request));
			p.requests = p.requests->next;
			p.requests->elements = NULL;
			p.last_i = ++p.i;
			p.requests->next = NULL;
			p.step = 0;
			while (p.s[p.i] == ' ')
				p.i++;
			continue;
		}
	}
	printf("end parsing\n");
	display_request(p.head);
}