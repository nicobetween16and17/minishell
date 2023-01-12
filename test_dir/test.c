#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

int main(int argc, char **argv, char **envp)
{
    int fd[2];
    fd[0] = open("caca.txt", O_CREAT | O_RDONLY, 0644);
    fd[1] = open("fart", O_CREAT | O_RDWR | O_TRUNC, 0644);
    char *tab[] = {"cat", NULL};
    dup2(fd[1], STDOUT_FILENO);
    close(fd[1]);
    execve("/bin/cat", tab, envp);
    printf("problemem d'execution");
    return (0);
}


