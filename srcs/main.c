/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niespana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 21:12:12 by niespana          #+#    #+#             */
/*   Updated: 2023/01/19 21:12:13 by niespana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishl.h"

/*
 * free the linked list allocated memory and the command line
 */
void	free_all(t_shell *sh)
{
	t_token *current;

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

/*
 * intercept the signals, displays the prompt with a crux or a 'v' depending
 * of the succes of the last command line. quit if the user uses ctrl+D
 * add the line in the history, replace the dollar signs, tokenize the line
 * and execute them. free the allocated line at the end.
 */
void	checkline(t_shell *shell)
{
	signal(SIGINT, &s_int);
	signal(SIGQUIT, &s_quit);
	if (shell->ret)
		ft_putstr_fd("❌ ", 2);
	else
		ft_putstr_fd("✔️ ", 2);
	shell->line = readline("\033[0;32mminishell> \033[0m");
	if (!shell->line)
		shell->exit = 1;
	else
	{
		if (g_signal.s_int == 1)
			shell->ret = g_signal.status;
		if (is_expandable(shell->line, ft_strlen(shell->line), 1))
			return ;
		free_completed_tab(shell->env);
		shell->env = get_env_tab(shell->env_lst);
		add_history(shell->line);
		line_plus_space(shell);
		replace_words(shell, -1, 0);
		parse(shell->line, shell);
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
	shell->ret = 0;
	shell->env = env_init((const char **)env);
	shell->env_lst = init_lst(shell->env);
	init_signal();
}

int	main(int ac, char **av, char **env)
{
	t_shell	shell;
	int		status;

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
		waitpid(-1, &status, 0);
	}
	free_completed_tab(shell.env);
	free_env_lst(shell.env_lst);
	//free(shell.tokens);
	//rl_clear_history();
	//system("leaks a.out");
	return (shell.ret);
}
