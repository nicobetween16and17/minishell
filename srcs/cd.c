#include "minishl.h"

int	ft_cd(char **params, t_shell *shell)
{
	int		dir;
	char	*path;

	if (!params || !params[0] || !params[1])
		return (1);
	path = params[1];
	(void)shell;
	dir = chdir(path);
	if (dir)
		printf("cd: string not in pwd: %s\n", path);
	return (0);
}