/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katalbi <katalbi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 21:12:12 by niespana          #+#    #+#             */
/*   Updated: 2023/04/04 11:43:17 by katalbi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishl.h"

/*
 * free the linked list allocated memory and the command line
 */
void	free_all(t_shell *sh)
{
	t_token	*current;

	current = xmalloc(1);
	while (sh->tokens)
	{
		free(current);
		current = sh->tokens;
		if (current->type == CMD)
			free_completed_tab(current->cmds);
		else
			free(current->filename);
		current->cmds = NULL;
		current->filename = NULL;
		sh->tokens = sh->tokens->next;
	}
	g_signal.fd_hdoc = -1;
	unlink(".heredoc.tmp");
	free(sh->line);
}

/*
 * add a space at the end of the string
 */
char	*line_plus_space(t_shell *shell)
{
	char	*line;
	int		i;

	i = -1;
	line = xmalloc((ft_strlen(shell->line) + 2) * sizeof(char *));
	while (shell->line[++i])
		line[i] = shell->line[i];
	line[i++] = 32;
	line[i] = 0;
	free(shell->line);
	shell->line = line;
	return (shell->line);
}
//TODO pipe redir not working properly, cat | cat | ls, pipe with multiple cat
//TODO potentially all the same error, pipe not closed correctly ?
/*
 * intercept the signals, displays the prompt with a crux or a 'v' depending
 * of the succes of the last command line. quit if the user uses ctrl+D
 * add the line in the history, replace the dollar signs, tokenize the line
 * and execute them. free the allocated line at the end.
 */
void	checkline(t_shell *shell)
{
	set_signal();
	shell->line = readline("\033[0;32mminishell> \033[0m");
	if (!shell->line)
		shell->exit = 1;
	else
	{
		if (is_expandable(shell->line, ft_strlen(shell->line), 1) || \
		(check_forbidden(shell->line) && (!safe_free(shell->line))))
			return ;
		free_completed_tab(shell->env);
		shell->env = get_env_tab(shell->env_lst);
		add_history(shell->line);
		line_plus_space(shell);
		replace_words(shell, -1, 0);
		if (empty_line(shell->line))
			return ;
		parse(shell->line, shell);
		g_signal.catcatls = is_catcatls(shell->tokens);
		exec_cmds(shell, shell->tokens->next);
		free_all(shell);
	}
}

/*
 * instantiate the shell and the environment variables
 */
void	init_shell(t_shell *shell, char **env)
{
	shell->tokens = NULL;
	shell->in = dup(0);
	shell->out = dup(1);
	shell->exit = 0;
	g_signal.ret = 0;
	g_signal.heredoc = 0;
	shell->env = env_init((const char **)env);
	shell->env_lst = init_lst(shell->env);
	if (!get_env_side(shell->env_lst, "SHLVL", NONE))
		add_env(&shell->env_lst, new_env(ft_strdup("SHLVL="), ft_strdup("1")));
	g_signal.fd_hdoc = -1;
	init_signal();
}

int	main(int ac, char **av, char **env)
{
	t_shell	shell;

	(void)ac;
	(void)av;
	init_shell(&shell, env);
	while (!shell.exit)
	{
		shell.infile = 0;
		shell.outfile = 1;
		checkline(&shell);
		close_fds(&shell);
		reset_std(&shell);
		reset_fds(&shell);
	}
	free_completed_tab(shell.env);
	free_env_lst(shell.env_lst);
	free(shell.tokens);
	unlink(".heredoc.tmp");
	rl_clear_history();
	return (g_signal.ret);
}
