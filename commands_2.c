#include "minishl.h"

char *output(char *cmd, int len, int i)
{
	char	*output;

	while (cmd && cmd[len] && cmd[len] != '|')
		len++;
	output = malloc(sizeof(char) * (i + 1));
	if (!output)
		return (NULL);
	while (cmd && cmd[++i])
		output[i] = cmd[i];
	output[i] = 0;
	return (output);
}

void	handle_ls(void)
{

}

void	handle_cat(void)
{

}

void	handle_echo(void)
{
	shell.history->command += 4;
	if (*shell.history->command)
		shell.history->command++;
	if (!strncmp(shell.history->command, "-n", 2))
	{
		shell.history->command += 2;
		shell.flag = 'n'
	}
	if (shell.output)
		free(shell.output);
	shell.output = output(cmd, 0, -1);
}
