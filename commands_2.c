#include "minishl.h"

char *output(char **cmd, int len, int i)
{
	char	*output;

	while (*cmd && (*cmd)[len] && (*cmd)[len] != '|')
		len++;
	output = malloc(sizeof(char) * (i + 1));
	if (!output)
		return (NULL);
	while (*cmd && *(*cmd))
	{
		output[i++] = *(*cmd);
		(*cmd)++;
	}
	output[i] = 0;
	return (output);
}

void	handle_ls(void)
{
	return ;
}

void	handle_cat(void)
{
	return ;
}

void	handle_echo(void)
{
	shell.current_cmd += 5;
	if (*shell.current_cmd)
		shell.history->command++;
	if (!strncmp(shell.current_cmd, "-n ", 3))
	{
		shell.current_cmd += 3;
		shell.flag = 'n';
	}
	if (shell.output)
		free(shell.output);
	shell.output = output(&shell.current_cmd, 0, 0);
	if (*shell.current_cmd)
		handle_parsing();
	else if (shell.flag == 'n')
	{
		printf("%s\033[5;47;30m%%\033[0m\n", shell.output);
	}
	else
		printf("%s\n", shell.output);
	//printf("%s\n",shell.current_cmd);

}
