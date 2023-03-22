#include "minishl.h"

void	ft_close(int fd)
{
	if (fd >= 0)
		close(fd);
}

void	reset_std(t_shell *sh)
{
	dup2(sh->in, 0);
	dup2(sh->out, 1);
}

void	close_fds(t_shell *sh)
{
	ft_close(sh->infile);
	ft_close(sh->outfile);
}

void	reset_fds(t_shell *sh)
{
	sh->infile = 0;
	sh->outfile = 1;
}
