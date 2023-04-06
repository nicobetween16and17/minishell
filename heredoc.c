/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niespana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 21:12:12 by niespana          #+#    #+#             */
/*   Updated: 2023/01/19 21:12:13 by niespana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishl.h"

/*
 * simple flag to say when you found a keyword
 */
int	set_last(t_utils *utils, int i)
{
	utils->last = i;
	return (1);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while ((s1[i] || s2[i]))
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

static void	setup_herdoc(char **delimiter, t_shell *sh, int *here_doc_file)
{
	g_signal.heredoc = 1;
	sh->tmp = ft_strjoin(*delimiter, "\n");
	*delimiter = sh->tmp;
	*here_doc_file = open(".heredoc.tmp", O_CREAT | O_RDWR | O_TRUNC, 0777);
}

/*
 * read standard input and put it in a hidden file as long as the line is
 * not uniquely composed of the stop word
 */
int	here_doc(char *delimiter, t_shell *sh)
{
	char	*buffer;
	int		here_doc_file;

	setup_herdoc(&delimiter, sh, &here_doc_file);
	if (here_doc_file < 0)
		return (here_doc_file);
	while (1)
	{
		set_signal();
		if (g_signal.heredoc == 0)
			break ;
		ft_putstr_fd("> ", 1);
		buffer = get_next_line(1);
		if (!buffer || ((ft_strlen(buffer) == ft_strlen(delimiter)) \
		&& !ft_strcmp(buffer, delimiter)))
			break ;
		else
			ft_putstr_fd(buffer, here_doc_file);
		buffer = safe_free(buffer);
	}
	buffer = safe_free(buffer);
	free(sh->tmp);
	g_signal.heredoc = 0;
	reset_std(sh);
	return (here_doc_file);
}

/*
 * returns the number of parameters
 */
int	nb_args(char **args)
{
	int		size;

	size = 0;
	while (args[size])
		size++;
	return (size);
}
