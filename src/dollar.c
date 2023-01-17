#include "../include/minishl.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s && s[i] != '\0')
		i++;
	return (i);
}

int	is_white_space(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
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

char	*ft_strchr(const char *s, int c)
{
	while (*s != '\0')
	{
		if (*(unsigned char *)s == (unsigned char)c)
			return ((char *)s);
		s++;
	}
	if (c == 0)
		return ((char *)s);
	return (NULL);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	if (ft_strlen(src) + 1 < size)
		ft_memcpy(dst, src, ft_strlen(src) + 1);
	else if (size > 0)
	{
		ft_memcpy(dst, src, size - 1);
		dst[size - 1] = '\0';
	}
	return (ft_strlen(src));
}

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dstlen;
	size_t	srclen;
	size_t	i;

	i = 0;
	dstlen = ft_strlen((const char *)dst);
	srclen = ft_strlen(src);
	if (size < dstlen)
		return (size + srclen);
	while (src[i] != '\0' && i + dstlen + 1 < size)
	{
		dst[dstlen + i] = src[i];
		i++;
	}
	dst[dstlen + i] = '\0';
	return (dstlen + srclen);
}

char *ft_strndup(char *s, size_t n)
{
    size_t i;
    char *new_s;
    i = 0;
    while (s[i] && i < n)
        i++;
    new_s = malloc((i + 1) * sizeof(char));
    if (!new_s)
    {
        printf("error");
        exit(0);
    }
    ft_strlcpy(new_s, s, i);
    new_s[i] = 0;
    return (new_s);
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

size_t	ft_nsize(long n, int size)
{
	if (n < 0)
		return (ft_nsize(-n, size + 1));
	if (n > 0)
		return (ft_nsize(n / 10, size + 1));
	return (size);
}

char	*ft_specials(int n)
{
	if (n == 0)
		return (ft_strdup("0"));
	return (ft_strdup("-2147483648"));
}

char	*ft_itoa(int n)
{
	char	*itoa;
	size_t	size;
	long	nb;

	nb = n;
	if (n == 0 || n == -2147483648)
		return (ft_specials(n));
	size = ft_nsize(nb, 0);
	itoa = malloc((size + 1) * sizeof(char));
	if (!itoa)
		return (0);
	if (n < 0)
		nb = -n;
	itoa[size] = '\0';
	while (nb > 0)
	{
		itoa[--size] = (nb % 10) + 48;
		nb = nb / 10;
	}
	if (n < 0)
		itoa[0] = '-';
	return (itoa);
}

char *ft_concat(char *s1, char *s2, size_t i)
{
    char *new;
    size_t len = i + ft_strlen(s2);
    new = malloc((len + 1) * sizeof(char));
    if (!new)
    {
        exit(0);
    }
    ft_strlcpy(new, s1, i);
    ft_strlcat(new, s2, len);
    return (new);
}

char *add_char_to_string(char *word, char c)
{
	char *new_word;

	if (!word)
	{
		word = malloc(2 * sizeof(char));
		word[0] = c;
		word[1] = 0;
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


void	put_in_the_middle(char **s, int *i, size_t n_char, char *for_middle)
{
	char *new_s;
	char *tmp;

	tmp = ft_strdup((*s) + (*i) + n_char);
	new_s = ft_strndup((*s), (size_t)((*i) + 1));
    new_s = ft_concat(new_s, for_middle, ft_strlen(new_s) + ft_strlen(for_middle));
    new_s = ft_concat(new_s, tmp, ft_strlen(new_s));
	(*i) += (ft_strlen(for_middle) - 2);
	(*s) = new_s;
	free(tmp);
}

int	double_dollar(char **s, int *i)
{
    pid_t pid;
    char    *pid_string;
    if ((*s)[(*i) + 1] != '$')
        return (1);
    pid = getpid();
    pid_string = ft_itoa(((int)pid)); 
    put_in_the_middle(s, i, 2, pid_string);
    free(pid_string);
    return (0);
}

int	var_exist(char *s, char **envp)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (envp[i])
	{
		if (!ft_strncmp(s, envp[i], ft_strlen(s)))
			return (i);
		i++;
	}
	return (-1);
}


char *get_env_value(char *envp)
{
	int i;
	char *env_value;
	size_t len;
	i = 0;
	while (envp[i] != '=')
	{
		i++;
	}
	i++;
	len = ft_strlen(envp + i);
	env_value = malloc((len + 1) * sizeof(char));
	ft_strlcpy(env_value, envp + i, ft_strlen(envp + i) + 1);
	return (env_value);
}

int	put_env_var(char **s, int *i, char **envp)
{
	char *word;
	char *env_value;
	int j;
	word = NULL;
	(*i)++;
	while (!ft_strchr("$<>\"'| ", (*s)[(*i)]))
	{
		word = add_char_to_string(word, (*s)[(*i)]);
		(*i)++;
	}
	printf("_%s_\n", word);
	j = var_exist(word, envp);
	printf("mon j:  %d\n", j);
	if (j >= 0)
	{
		env_value = get_env_value(envp[j]);
		printf("mon env_value: %s\n", env_value);
		put_in_the_middle(s, i, ft_strlen(env_value), env_value);
	}
	else
	{
		put_in_the_middle(s, i, 1, " ");
	}
	free(word);
	return (0);
}

int	single_dollar(char c)
{
	if (is_white_space(c) || ft_strchr("|\0", c))
		return (0);
	return (1);
}

void    replace_dollar(char **s, int *i, char **envp)
{
        if ((*s)[(*i)] == '$' )
        {
            if (!double_dollar(s, i) || !put_env_var(s, i, envp))
				;
        }
}

int main(int argc, char **argv, char **envp)
{
    int i;

    i = 0;
    char *s = "bliblaboui$bonjour a toi comment vas tu";
	while (s[i])
	{
    	if (s[i] == '$')
		{
        	replace_dollar(&s, &i, envp);
		}
		i++;
	}
    printf("%s", s);
}