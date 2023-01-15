#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

void    further_string(char *s)
{
    int i = 0;
    while (i++ < 5)
    {
        s++;
    }
    printf("%s\n", s);
}

void escale(char **s)
{
    further_string(*s);
}

int main(int argc, char **argv, char **envp)
{
    printf("%c%c\n", '\'', '\"');
}



