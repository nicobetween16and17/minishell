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
/*typedef struct s_pipe
{
	char	**crt;
	char	*cmd;
	pid_t	pid;
	int		len;
	int		n;
	int		fd[200][2];
	int		status;
}t_pipe;
*/
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

void	exec_cmds(t_list *cmds, char **env)
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
			if (pipex.n < pipex.len - 1 && dup2(pipex.fd[pipex.n][1], 1) < 0)
				exit(1);
			if (pipex.n && dup2(pipex.fd[pipex.n - 1][0], 0) < 0)
				exit(1);
			execve(pipex.cmd, pipex.crt, env);
		}
		waitpid(pipex.pid, &pipex.status, 0);
		if (pipex.n < pipex.len - 1 && close(pipex.fd[pipex.n][1]))
			exit(0);
		if (pipex.n && close(pipex.fd[pipex.n - 1][0]))
			exit(0);
		cmds = cmds->next;
		pipex.n++;
		free(pipex.cmd);
	}
}

int main(int argc, char **argv, char **env){
	t_list *cmds;
	char **split;
	int i;
	i = 0;


	cmds = ft_lstnew(NULL);
	while (argv[++i]) {
		split = ft_split(argv[i], ' ');
		ft_lstadd_back(&cmds, ft_lstnew(split));
	}
	/*t_list *start;
	start = cmds;
	cmds = cmds->next;
	while (cmds)
	{
		i = -1;
		char **crt = (char **)cmds->content;
		while (crt[++i])
			printf("%d: %s\n", i, crt[i]);
		printf("\n");
		cmds = cmds->next;
	}
	cmds = start;*/
	exec_cmds(cmds->next, env);
}
