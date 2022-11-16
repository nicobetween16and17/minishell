#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int main(int ac, char **av, char **env)
{
	int i = 0;
	//execve("/Users/nico/Documents/mini/echo", ++av, env);
	while (i < 10)
	{
		i++;
		if (i == 5)
			continue;
		printf("%d\n", i);
	}
}