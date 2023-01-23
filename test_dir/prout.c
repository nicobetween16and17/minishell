#include "../minishl.h"



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

char *ft_strndup(char *s, size_t n)
{
    int i;
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

char *name_env_var(char *s)
{
    int i;
    char *new;
    i = 0;
    while (s[i] && s[i] != '=')
    {
        i ++;
    }
    if (s[i] != '=')
    {
        printf("not a valid identifier");
        exit(0);
    }
    new = ft_strndup(s, i + 1);
    return (new);
}



int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] || s2[i] && i < n)
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
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

int check_arg(char *s)
{
    int i;
    
    i = 0;
    while (s[i] && s[i] != '=')
    {
        i++;
    }
    if (s[i] == '=' && i == 0)
    {
        printf("invalid identifier");
        exit(0);
    }
    if (s[i] == 0)
        return (-1);
    return (i);
}


char **erase_env_var(int i, char **envp)
{
    int j;
    j = 0;
    char **new_envp;

    while (envp[j])
    {
        j++;
    }
    new_envp = malloc(j * sizeof(char*));
    if (!new_envp)
    {
       printf("malloc problem");
        exit(0);
    }
    j = 0;
    while(j < i)
    {
        new_envp[j] = ft_strdup(envp[j]);
        j++;
    }
    j++;
    while (envp[j])
    {
        new_envp[j] = ft_strdup(envp[j]);
        j++;
    }
    new_envp[j] = NULL;


    return (new_envp);
}

char **add_back_tab(char **tab, char *s)
{
    int i;
    char **new_tab;
    i = 0;
    while(tab[i])
        i++;
    new_tab = malloc((i + 2) * sizeof(char *));
    i = 0;
    while (tab[i])
    {
        new_tab[i] = ft_strdup(tab[i]);
        i++;
    }
    new_tab[i] = ft_strdup(s);
    new_tab[i + 1] = NULL;
    return (new_tab);
}

char **change_var(char *s, char **envp)
{
    int i;

    i = 0;
    i = check_arg(s);
    if (i < 0)
        return (envp);
    i = 0;
    printf("GRAAAAAAAAA\n");
    while (envp[i])
    {
        printf("SALUT\n");
        if (!ft_strncmp(name_env_var(s), name_env_var(envp[i]), ft_strlen(s)))
        {
            printf("coucou\n");
            envp = erase_env_var(i, envp);
        }
        i++;
    }
    printf("flop%d\n", i);
    envp = add_back_tab(envp, s);
    return (envp);
}

int main(int argc, char **argv, char **envp)
{
    int i;

    i = 0;
    char *s = "bonjouratous";
    envp = change_var("bonjour=prout", envp);
    while (envp[i])
    {
        printf("%s\n", envp[i]);
        i++;
    }

}

rien a voir