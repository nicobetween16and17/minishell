#include <stdio.h>
#include <string.h>
int main()
{
	char *test = "\033[0;31m";
	printf("%lu\n", strlen(test));
	printf("\\033[0;31m\n");
	printf("\"");
}