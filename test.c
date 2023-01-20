/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niespana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 15:05:02 by niespana          #+#    #+#             */
/*   Updated: 2023/01/13 15:05:04 by niespana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include "minishl.h"
#include "libft/libft.h"

typedef struct s_utils
{
	int		i;
	int		cmd;
	int		last;
	t_list	*tokens;
	char	*tmp;
}t_utils;

typedef struct s_utils2
{
	char	*sub;
	int		i;
	int		nbq;
	int		j;
	int		f;
}	t_utils2;

int	contain(char c, char *s)
{
	int	i;

	i = -1;
	if (c == '$')
	{
		while (s && s[++i])
		{
			if (s[i] == c && s[i + 1] != ' ')
				return (1);
		}
		return (0);
	}
	while (s && s[++i])
	{
		if (s[i] == c)
			return (1);
	}
	return (0);
}

int	is_btwn_q(char *s, int i)
{
	int	sgl;
	int	dbl;
	int	j;

	sgl = 0;
	dbl = 0;
	j = -1;
	while (s && s[++j] && j < i)
	{
		((!sgl && !dbl && s[j] == '\"' && ++dbl) || (!dbl && !sgl \
		&& s[j] == '\'' && ++sgl) || (!sgl && dbl && s[j] == '\"' \
		&& dbl--) || (!dbl && sgl && s[j] == '\'' && sgl--));
	}
	return (sgl || dbl);
}

char	*sub(char *s, int len)
{
	t_utils2	u;

	u.f = 0;
	u.j = 0;
	u.nbq = 0;
	u.i = -1;
	while (s[++u.i])
		if (!is_btwn_q(s, u.i) && s[u.i] == '\"' || s[u.i] == '\'')
			u.nbq++;
	u.i = -1;
	u.sub = malloc(sizeof(char) * (len + 1 - u.nbq));
	while (s[++u.i] && u.i < len)
	{
		if (!((s[u.i] == '\"' || s[u.i] == '\'' || s[u.i] == ' ') \
		&& !is_btwn_q(s, u.i + u.f)))
		{
			if (u.f)
				u.f = 0;
			else
				u.f = 1;
			u.sub[u.j++] = s[u.i];
		}
	}
	u.sub[u.j] = 0;
	return (u.sub);
}

int	is_charset(char c, char *charset)
{
	while (charset && *charset)
		if (c == *charset++)
			return (1);
	return (0);
}

int	cut_until(char *s, t_utils *utils, char *stop)
{
	int	start;
	int	len;

	len = 1;
	start = utils->i;
	if (stop == NULL)
	{
		stop = &s[utils->i];
		while (s[utils->i + len] && s[utils->i + len] == stop[0])
			len++;
	}
	else
	{
		while (s[utils->i + len] && (is_btwn_q(s, utils->i + len) \
		|| !is_charset(s[utils->i + len], stop)))
			len++;
	}
	utils->tmp = sub(s + start, len);
	if (strlen(utils->tmp))
		ft_lstadd_back(&utils->tokens, ft_lstnew(utils->tmp));
	else
		free(utils->tmp);
	utils->i += len;
	return (1);
}

int	set_last(t_utils *utils, int i)
{
	utils->last = i;
	return (1);
}

int	ft_free(void *content)
{
	free(content);
	return (1);
}

void	setup_cmd2(t_list *new, t_shell *sh)
{
	char	**current_cmd;
	t_list	*head;
	int		i;

	i = 0;
	head = new;
	sh->cmd = ft_lstnew(NULL);
	while (new && ft_strncmp((char *)new->content, "|", 2) && ++i)
		new = new->next;
	current_cmd = malloc(sizeof(char *) * ++i);
	new = head;
	i = 0;
	while (new && ft_strncmp((char *)new->content, "|", 2))
		current_cmd[i++] = (char *)new->content;
	current_cmd[i++] = (char *)new->content;
	current_cmd[i] = 0;
	ft_lstadd_back(&sh->cmd, (void *)current_cmd);
	if (new && new->next)
		setup_cmd2(new->next, sh);
}

void	setup_cmd(t_list *tokens, t_shell *shell, char *f)
{
	t_list	*new;

	new = ft_lstnew(NULL);
	while (tokens)
	{
		if ((((char *)tokens->content)[0] == '>' \
		|| ((char *)tokens->content)[0] == '<') && tokens->next)
			f = (char *)tokens->next->content;
		if (!ft_strncmp((char *)tokens->content, "<", 2))
		{
			shell->infile = open(f, O_RDWR);
			if (shell->infile == -1 && shell->infile++)
				printf("%s: permission denied\n", f);
		}
		else if (!ft_strncmp((char *)tokens->content, "<<", 3))
			shell->heredoc = NULL;
		else if (!ft_strncmp((char *)tokens->content, ">", 2))
			shell->outfile = open(f, O_RDWR | O_CREAT | O_APPEND, 0644);
		else if (!ft_strncmp((char *)tokens->content, ">>", 3))
			shell->outfile = open(f, O_RDWR | O_APPEND | O_CREAT, 0644);
		else if (!ft_strncmp((char *)tokens->content, f, ft_strlen(f + 1)))
			ft_lstadd_back(&new, tokens);
		tokens = tokens->next;
	}
	setup_cmd2(new->next, shell);
}

void	test_parse(char *s, t_shell *sh)
{
	t_utils	utils;

	utils.last = 0;
	utils.tokens = ft_lstnew(NULL);
	utils.i = 0;
	utils.cmd = 1;
	while (s[utils.i])
	{
		(((s[utils.i] == '<' || s[utils.i] == '>') && set_last(&utils, 1) && \
		!is_btwn_q(s, utils.i) && cut_until(s, &utils, NULL)) || \
		(s[utils.i] == '|' && set_last(&utils, 1) && !is_btwn_q(s, utils.i) && \
		cut_until(s, &utils, NULL)) || (utils.i == 0 && !is_btwn_q(s, utils.i) \
		&& cut_until(s, &utils, " ")) || ((s[utils.i] == ' ' || !s[utils.i] || \
		(utils.last && set_last(&utils, 0))) && !is_btwn_q(s, utils.i) && \
		cut_until(s, &utils, " |<>") || ++utils.i));
	}
	utils.tmp = "";
	utils.tokens = utils.tokens->next;
	setup_cmd(utils.tokens, &sh, utils.tmp);
}

int	main(int ac, char **av, char **env)
{
	t_shell	shell;

	test_parse(av[1], &shell);
}
