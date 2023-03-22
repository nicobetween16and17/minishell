#include "minishl.h"

int here_doc(char *delimiter)
{
	char *buffer;
	int here_doc_file;
	int j;

	j = 0;
	here_doc_file = open(".heredoc.tmp", O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (here_doc_file < 0)
		return (here_doc_file);
	while(1)
	{
		buffer = readline("> ");
		if (!ft_strncmp(buffer, delimiter, ft_strlen(buffer))\
		&& ft_strlen(buffer) == ft_strlen(delimiter))
			break ;
		else
		{
			if (j)
				write (here_doc_file, "\n", 1);
			else
				j++;
			ft_putstr_fd(buffer, here_doc_file);
		}
	}
	return (here_doc_file);
}