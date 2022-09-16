#include "minishl.h"

void	handle_ls(void)
{
	return ;
}

void	handle_cat(void)
{
	return ;
}

void handle_backslash(char *cmd, int i)
{
	if (!strncmp("033", &cmd[i], 3))
		shell.output[]("\033");
	if (cmd[i] == 'n')
		printf("\n");
	if (cmd[i] == 't')
		printf("\t");
	if (cmd[i] == 'r')
		printf("\r");
	if (cmd[i] == 'f')
		printf("\f");
	if (cmd[i] == 'v')
		printf("\v");
	if (cmd[i] == 'e')
		printf("\033");
}
void	handle_echo(int mode)
{
	int	i;
	int	flag;
	char *cmd;

	if ((!mode % 2) && shell.output)
		free(shell.output);
	shell.output = malloc(sizeof(char) * (strlen(shell.content) + 1))
	cmd = shell.content;
	flag = 0;
	i = -1;
	while (shell.current_cmd.flags[++i])
		if (shell.current_cmd.flags[i] == 'n')
			flag = 1;
		i = -1;
	while (cmd && cmd[++i])
	{
		if (cmd[i] == '\"' && i++)
			mode++;
		if (cmd[i] == '\\' && i++)
		{
			if (mode % 2)
				handle_backslash(cmd, i)
			else if (cmd[i] == '\\' && i++)
				handle_backslash(cmd, i)
			else
				write(1, &cmd[i],1)
		}
		else
			write(1, &cmd[i],1)
	}
	if (mode % 2)
	{
		shell.content = readline("dquotes> ");

	}

}
