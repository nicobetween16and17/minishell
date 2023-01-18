#include "../include/minishl.h"

void	cd(char *path)
{
	int dir;

	if (!path)
		return;
	dir = chdir(path);
	if (dir)
		printf("cd: string not in pwd: %s", path);
}