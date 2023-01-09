#include <unistd.h>
#include <string.h>
#include <stdio.h>

int main(void)
{
	char *test = "je cherche l'occurence";
	char *occu = strnstr(test, "cherche", 300);

	while (test && *test)
	{
		if (test == occu)
			printf("OoOoOOoOoOoOOooOOOoOoOO\n");
		printf("[%s] == [%s]\n", test++, occu);
	}
}