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

void	free_token(t_token *current)
{
	if (current->cmds == CMD)
		free_completed_tab(current->cmds);
	else
		free(current->filename);
	current->cmds = NULL;
	current->filename = NULL;
}

void	checkline(t_shell *shell)
{
	char	*line;

	signal(SIGINT, &s_int);
	signal(SIGQUIT, &s_quit);
	if (shell->ret)
		ft_putstr_fd("❌ ", 2);
	else
		ft_putstr_fd("✔️ ", 2);
	line = readline("\033[0;32mminishell> \033[0m");
	if (!line)
		exit(shell->ret);
	else
	{
		if (g_signal.s_int == 1)
			shell->ret = g_signal.status;
		if (is_expandable(line, ft_strlen(line), 1))
			return ;
		shell->line = line;
		add_history(line);
		replace_words(shell, -1, 0);
		parse(shell->line, shell);
		shell->tokens = shell->tokens->next;
		free(line);
		line = NULL;
	}
}

void	init_shell(t_shell *shell, char **env)
{
	shell->tokens = NULL;
	shell->in = dup(0);
	shell->out = dup(1);
	shell->exit = 0;
	shell->ret = 0;
	shell->no_exec = 0;
	shell->env = env_init((const char **)env);
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
		exec_cmds(&shell, shell.tokens);
		close_fds(&shell);
		reset_std(&shell);
		reset_fds(&shell);
		waitpid(-1, &status, 0);
		status = WEXITSTATUS(status);
		if (shell.ret)
			shell.ret = status;
	}
	return (0);
}
