#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include "minishl.h"
#include "libft/libft.h"

typedef struct path
{
	int	coins;
	int	exit;
}	t_path;

void	ft_path(t_path *path, char **map, int y, int x)
{
	if (((map[y + 1][x] == 'C' && path->coins++) || (map[y + 1][x] == 'E'
		&& path->exit++) || 1) && map[y + 1][x] != '1')
	{
		map[y + 1][x] = '1';
		ft_path(path, map, y + 1, x);
	}
	if (((map[y - 1][x] == 'C' && path->coins++) || (map[y - 1][x] == 'E'
		&& path->exit++) || 1) && map[y - 1][x] != '1')
	{
		map[y - 1][x] = '1';
		ft_path(path, map, y - 1, x);
	}
	if (((map[y][x + 1] == 'C' && path->coins++) || (map[y][x + 1] == 'E'
		&& path->exit++) || 1) && map[y][x + 1] != '1')
	{
		map[y][x + 1] = '1';
		ft_path(path, map, y, x + 1);
	}
	if (((map[y][x + 1] == 'C' && path->coins++) || (map[y][x + 1] == 'E'
		&& path->exit++) || 1) && map[y][x + 1] != '1')
	{
		map[y][x + 1] = '1';
		ft_path(path, map, y, x + 1);
	}
}

int	main(int ac, char **av, char **env)
{
	t_path	path;

	path.coins = 0;
	path.exit = 1;
	ft_path(&path, av, 1, 1);
	return (0);
}
