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
	printf("path %s\n", res);
	return (res);
}
typedef struct s_pipe
{
	char	**crt;
	char	*cmd;
	pid_t	pid;
	int		len;
	int		n;
	int		fd[200][2];
}t_pipe;
void	close_all_fd(t_pipe *pipe)
{
	int	i;

	i = -1;
	while (++i < pipe->len - 1)
	{

		close(pipe->fd[i][0]);
		close(pipe->fd[i][1]);
	}
}
/*
 * PAIRE fd[n][0] fd[n][1]
 * IMPAIRE fd[n][1] fd[n + 1][0]
 */
int exec_cmd(t_list *cmd, char **env)
{
	pid_t	pid;
	int		ret;
	int		status;
	int		pipe_open;

	ret = EXIT_FAILURE;
	pipe_open = 0;
	if (cmd->type == TYPE_PIPE || (cmd->previous && cmd->previous->type == TYPE_PIPE))
	{
		pipe_open = 1;
		if (pipe(cmd->pipes))
			return (exit_fatal());
	}
	pid = fork();
	if (pid < 0)
		return (exit_fatal());
	else if (pid == 0)
	{
		if (cmd->type == TYPE_PIPE
			&& dup2(cmd->pipes[SIDE_IN], STDOUT) < 0)// dup2(fd[n][1], 1)
			return (exit_fatal());
		if (cmd->previous && cmd->previous->type == TYPE_PIPE // if (n && dup2(fd[n - 1][0], 0))
			&& dup2(cmd->previous->pipes[SIDE_OUT], STDIN) < 0)
			return (exit_fatal());
		if ((ret = execve(cmd->args[0], cmd->args, env)) < 0)
		{
			show_error("error: cannot execute ");
			show_error(cmd->args[0]);
			show_error("\n");
		}
		exit(ret);
	}
	else
	{
		waitpid(pid, &status, 0);
		if (pipe_open)
		{
			close(cmd->pipes[SIDE_IN]);
			if (!cmd->next || cmd->type == TYPE_BREAK)
				close(cmd->pipes[SIDE_OUT]);
		}
		if (cmd->previous && cmd->previous->type == TYPE_PIPE)
			close(cmd->previous->pipes[SIDE_OUT]);
		if (WIFEXITED(status))
			ret = WEXITSTATUS(status);
	}
	return (ret);
}
void	exec_cmds(t_list *cmds, char **env)
{
	t_pipe pipex;

	pipex.n = 0;

	pipex.len = ft_lstsize(cmds);
	printf("len = %d\n", pipex.len);
	while (pipex.n < pipex.len - 1)
		pipe(pipex.fd[pipex.n++]);
	pipex.n = 0;
	while (cmds)
	{
		pipex.crt = (char **)cmds->content;
		pipex.cmd = get_path(pipex.crt[0]);
		pipex.pid = fork();

		if (pipex.pid == 0)
		{
			printf("start child\n");
			if (!(pipex.n % 2) || !pipex.n)
				dup2(pipex.fd[pipex.n][1], STDOUT_FILENO);
			else
				dup2(pipex.fd[pipex.n][0], STDIN_FILENO);
			system("echo test >> test2");
			close_all_fd(&pipex);
			execve(pipex.cmd, pipex.crt, env);
		}
		printf("end child\n");
		cmds = cmds->next;
		pipex.n++;
		free(pipex.cmd);
	}
	close_all_fd(&pipex);
	waitpid(pipex.pid, NULL, 0);
}

int main(int argc, char **argv, char **env){
	t_list *cmds;
	char **split;
	int fd_s[2];
	int i;
	i = 0;


	cmds = ft_lstnew(NULL);
	while (argv[++i]) {
		split = ft_split(argv[i], ' ');
		ft_lstadd_back(&cmds, ft_lstnew(split));
	}
	t_list *start;
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
	cmds = start;
	exec_cmds(cmds->next, env);
}
