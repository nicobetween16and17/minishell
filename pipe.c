#include "minishl.h"

char *get_path(char *cmd) {
	int i;
	char **paths;
	char *cmd_path;
	char *res;

	cmd_path = ft_strjoin("/", cmd);
	i = -1;
	paths = ft_split(getenv("PATH"), ':');
	res = ft_strjoin(paths[0], cmd_path);
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

void init_pipe(t_pipe *pipex, t_list *cmds)
{
	pipex->n = 0;
	pipex->len = ft_lstsize(cmds);
	while (pipex->n < pipex->len - 1)
	{
		if (pipe(pipex->fd[pipex->n++]))
			exit(1);
	}
	pipex->n = 0;
}

void	exec_cmds(t_shell *shell, t_list *cmds)
{
	t_pipe pipex;

	init_pipe(&pipex, cmds);
	while (cmds)
	{
		pipex.crt = (char **)cmds->content;
		pipex.cmd = get_path(pipex.crt[0]);
		pipex.pid = fork();
		if (pipex.pid == 0)
		{
			dup2(pipex.fd[pipex.n][1], shell->outfile);
			(pipex.n && dup2(pipex.fd[pipex.n - 1][0], shell->infile));
			execve(pipex.cmd, pipex.crt, shell->env);
		}
		waitpid(pipex.pid, &pipex.status, 0);
		if (close(pipex.fd[pipex.n][1]))
			exit(1);
		if (pipex.n && close(pipex.fd[pipex.n - 1][0]))
			exit(1);
		cmds = cmds->next;
		pipex.n++;
		free(pipex.cmd);
	}
}