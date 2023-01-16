#include "minishl.h"


int	check_here_doc_access(fd)
{
	if (fd < 0)
	{
		if (check_access_of_file(cmd, &word, s, i))
            return (1);
        if (check_access_of_file(cmd, &word, s, i))
            return (1);
        if (check_access_of_file(cmd, &word, s, i))
            return (1);
	}
}

int here_doc(char *delimiter)
{
	char *buffer;
	int here_doc_file;
	int j;

	j = 0;
	here_doc_file = open (HEREDOC, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (check_here_doc_access(here_doc_file))
		return (1);
	while(1)
	{
		buffer = readline("> ");
		if (!ft_strncmp(buffer, delimiter, ft_strlen(buffer)) && ft_strlen(buffer) == ft_strlen(delimiter))
			break ;
		else
		{
			if (j)
				write(here_doc_file, "\n", 1);
			else
				j++;
			write(here_doc_file, buffer, ft_strlen(buffer));
		}
	}
	close(here_doc_file);
	return (here_doc_file);
}