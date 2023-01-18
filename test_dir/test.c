#include "../minishl.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>


size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s && s[i] != '\0')
		i++;
	return (i);
}

void	*ft_memcpy(void *s1, const void *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (!s1 && !s2)
		return (0);
	while (i < n)
	{
		*(char *)s1 = *(char *)s2;
		i++;
		s1++;
		s2++;
	}
	while (i > 0)
	{
		i--;
		s1--;
	}
	return (s1);
}


size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	int	i;

	i = -1;
	if (ft_strlen(src) == 1)
		dest[0] = 0;
	if (size != 0)
	{
		while (src[++i] && (size--) - 1)
			dest[i] = src[i];
		dest[i] = 0;
	}
	return (ft_strlen(src));
}

char	*ft_strdup(const char *s1)
{
	char	*cpy;
	size_t	i;

	i = 0;
	cpy = malloc((ft_strlen(s1) + 1) * sizeof(char));
	if (!cpy)
		return (0);
	while (s1[i])
	{
		cpy[i] = s1[i];
		i++;
	}
	cpy[i] = '\0';
	return (cpy);
}

char *add_char_to_string(char *word, char c)
{
	char *new_word;

	if (!word)
	{
		word = malloc(2 * sizeof(char));
		word[0] = c;
		return (word);
	}
	size_t len = ft_strlen(word);
	new_word = malloc((len + 2) * sizeof(char));
	ft_strlcpy(new_word, word, ft_strlen(word) + 1);
	new_word[len] = c;
	new_word[len + 1] = 0;
	free(word);
	return (new_word);
}

void autre_fonction(int *i)
{
    printf("le i dans autre fonction");
}

void    fonction(int *i)
{
    printf("le i dans fonction %d", *i);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while ((s1[i] || s2[i]) && i < n)
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

void	handler(int n)
{
	char c = (char)n + 48;
	write(1,&c, 1);
}

int main(int argc, char **argv, char **envp)
{
	struct sigaction sa;
	int x = 98;
	char i = (char)x;
	sa.sa_flags = SA_RESTART;
	sa.sa_handler = &handler;
    sigaction(SIGKILL, &sa, NULL);
	while (1)
		;
}



