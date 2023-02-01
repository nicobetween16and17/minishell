/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse0.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niespana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 21:12:12 by niespana          #+#    #+#             */
/*   Updated: 2023/01/19 21:12:13 by niespana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishl.h"

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

void	setup_cmd2(t_list *new, t_shell *sh)
{
	char	**current_cmd;
	t_list	*head;
	int		i;

	i = 0;
	head = new;
	while (new && ft_strncmp((char *)new->content, "|", 2) && ++i)
		new = new->next;
	current_cmd = xmalloc(sizeof(char *) * ++i);
	new = head;
	i = 0;
	while (new && ft_strncmp((char *)new->content, "|", 2))
	{
		current_cmd[i++] = new->content;
		new = new->next;
	}
	current_cmd[i] = 0;
	ft_lstadd_back(&sh->cmd, ft_lstnew(current_cmd));
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
			shell->outfile = open(f, O_RDWR);
			if (shell->infile == -1 && shell->infile++)
				printf("%s: permission denied\n", f);
		}
		else if (!ft_strncmp((char *)tokens->content, "<<", 3))
			shell->infile = here_doc(f);
		else if (!ft_strncmp((char *)tokens->content, ">", 2))
			shell->infile = open(f, O_RDWR | O_CREAT | O_APPEND, 0644);
		else if (!ft_strncmp((char *)tokens->content, ">>", 3))
			shell->infile= open(f, O_RDWR | O_APPEND | O_CREAT, 0644);
		else if (ft_strncmp((char *)tokens->content, f, ft_strlen(f + 1)))
			ft_lstadd_back(&new, ft_lstnew(tokens->content));
		tokens = tokens->next;
	}
	setup_cmd2(new->next, shell);
}

void	parse(char *s, t_shell *sh)
{
	t_utils	utils;

	utils.last = 0;
	utils.tokens = ft_lstnew(NULL);
	utils.i = 0;
	utils.cmd = 1;
	while (s[utils.i])
	{
		((((s[utils.i] == '<' || s[utils.i] == '>') && set_last(&utils, 1) && \
		!is_btwn_q(s, utils.i) && cut_until(s, &utils, NULL)) || \
		(s[utils.i] == '|' && set_last(&utils, 1) && !is_btwn_q(s, utils.i) && \
		cut_until(s, &utils, NULL)) || (utils.i == 0 && !is_btwn_q(s, utils.i) \
		&& cut_until(s, &utils, " ")) || ((s[utils.i] == ' ' || !s[utils.i] || \
		(utils.last && set_last(&utils, 0))) && !is_btwn_q(s, utils.i) && \
		cut_until(s, &utils, " |<>")) || ++utils.i));
	}
	utils.tmp = "";
	utils.tokens = utils.tokens->next;
	sh->cmd = ft_lstnew(NULL);
	setup_cmd(utils.tokens, sh, utils.tmp);
}
