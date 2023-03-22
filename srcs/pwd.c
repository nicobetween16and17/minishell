#include "minishl.h"

int ft_pwd(char **params, t_shell *shell)
{
	char *buf;

	(void)params;
	(void)shell;
	buf = getcwd(NULL, 0);
	ft_putstr_fd(buf, 1);
	write(1,"\n",1);
	free(buf);
	return (0);
}
