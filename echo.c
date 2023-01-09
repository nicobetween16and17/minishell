#include <unistd.h>
#include <stdlib.h>
#include "Libft/libft.h"
#include <stdio.h>

int	only_n(char *flag)
{
	while (flag && *flag) {
		if (*flag != 'n' && *flag != 0)
			return (0);
		flag++;
	}
	return (1);
}

void	display_echo(char **av, int i)
{
	while (av[++i])
	{
		while (*(av[i]))
		{
			write(1, av[i]++, 1);
		}
		if (av[i + 1])
			write(1, " ", 1);
	}
}

int	echo(char **to_display, char **env)
{
	int	new_line;
	int	i;

	new_line = 1;
	if (to_display && to_display[0][0] == '-' && only_n(to_display[0]))
		new_line = 0;
	i = 0;
	if (!new_line)
		i++;
	display_echo(to_display, i, env);
	if (new_line)
		write(1, "\n", 1);
	return (0);
}
