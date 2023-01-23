#include "../include/minishl.h"
char *pwd()
{
	char buf[400];
	return (getcwd(buf, 400));
}