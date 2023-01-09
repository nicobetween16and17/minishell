#include <stdio.h>
#include "libft/libft.h"

void	replace(char *str, char *search, char *replace)
{
	char	*ptr;
	int		search_len;
	int		replace_len;

	ptr = str;
	search_len = ft_strlen(search);
	replace_len = ft_strlen(replace);
	ptr = ft_strnstr(ptr, search, ft_strlen(ptr));
	while (ptr != NULL)
	{
		ft_memmove(ptr + replace_len, ptr + search_len,
				   ft_strlen(ptr + search_len) + 1);
		ft_memcpy(ptr, replace, replace_len);
		ptr += replace_len;
		ptr = ft_strnstr(ptr, search, ft_strlen(ptr));
	}
}


int main()
{
	char str[] = "Hello, world! How are you doing?";
	replace(str, "world", "girwioggrgirjgiurghiu");
	printf("%s\n", str);
	return 0;
}
