#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int main(int ac, char **av, char **env)
{
	execve("/Users/nico/Documents/mini/echo", ++av, env);
}