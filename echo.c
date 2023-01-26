#include "minishl.h"

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

void	ft_echo(char **to_display, t_shell *shell)
{
	int	new_line;
	int	i;

	(void)shell;
	new_line = 1;
	if (to_display && to_display[0][0] == '-' && only_n(to_display[0]))
	{
		to_display++;
		new_line = 0;
	}
	i = 0;
	if (!new_line)
		i++;
	display_echo(to_display, i);
	if (new_line)
		write(1, "\n", 1);
}
