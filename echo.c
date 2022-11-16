#include <unistd.h>

int	ft_strlen(char *s)
{
	char	*start;

	start = s;
	while (s && *s)
		s++;
	return (s - start);
}

int	check_flags(char *s, int *i)
{
	int	k;

	k = -1;
	if (ft_strlen(s) == 1)
	{
		*i = 0;
		return (0);
	}
	while (s && s[++k])
	{
		if (k >= 1 && s[k] == ' ')
		{
			*i = 0;
			return (0);
		}
		if (s[k] == 'n')
			return (1);
	}
	return (0);
}

int	main(int ac, char **av)
{
	int	i;
	int	flag;

	flag = 0;
	i = 0;
	if (ac < 2)
		return (1);
	if (*(av[1]) == '-')
		i++;
	if (i)
		flag = check_flags(av[1], &i);
	while (++i < ac)
	{
		while (*(av[i]))
			write(1, av[i]++, 1);
		if (i < ac - 1)
			write(1, " ", 1);
	}
	if (!flag)
		write(1, "\n", 1);
	return (0);
}
