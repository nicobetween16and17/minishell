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

#include "minishl.h"

char *get_path(char *cmd) {
	int i;
	char **paths;
	char *cmd_path;
	char *res;

	cmd_path = ft_strjoin("/", cmd);
	i = -1;
	paths = ft_split(getenv("PATH"), ':');
	res = ft_strjoin(paths[i], cmd_path);
	while (access(res, X_OK) && paths[++i]) {
		free(res);
		res = ft_strjoin(paths[i], cmd_path);
	}
	free(cmd_path);
	i = -1;
	while (paths[++i])
		free(paths[i]);
	free(paths);
	return (res);
}

void	exec_cmds(t_list *cmds, int fds[2], char **env)
{
	char	**crt;
	int		i;
	char	*cmd;
	pid_t	pid;
	int k = -1;

	if (pipe(fds) == -1)
		exit(0);
	crt = (char **)cmds->content;
	while (crt[++k])
		printf("%d %s\n", k, crt[k]);
	cmd = get_path(crt[0]);
	printf("%s\n", cmd);
	pid = fork();
	if (!pid)
		execve(cmd, crt, env);
	else
	{
		i = -1;
		free(cmd);
		if (cmds->next)
		{
			while (crt[++i])
				free(crt[i]);
			free(crt);
			exec_cmds(cmds->next, fds, env);
		}
	}
}

int main(int argc, char **argv, char **env)
{
	t_list *cmds;
	char **split;
	int fd_s[2];
	int i;

	i = 0;
	fd_s[0] = 0;
	fd_s[1] = 1;

	cmds = ft_lstnew(NULL);
	while (argv[++i])
	{
		split = ft_split(argv[i], ' ');
		ft_lstadd_back(&cmds, ft_lstnew(split));
	}
	exec_cmds(cmds->next, fd_s, env);
}