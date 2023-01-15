#include "minishl.h"

void	free_string(char *s)
{
	if (s)
		free(s);
}

void    switch_quote(char *s, char *quote, int *i)
{
    while (s[*i] && ft_strchr("\"'", s[*i]))
	{
		if (s[*i] == *quote)
			*quote = 0;
		else if (!(*quote))
			*quote = s[*i];
		(*i)++;
	}
}

char *add_char_to_string(char *word, char c)
{
	char *new_word;

	if (!word)
	{
		word = malloc(2 * sizeof(char));
		word[0] = c;
		return (word);
	}
	size_t len = ft_strlen(word);
	new_word = ((len + 2) * sizeof(char));
	ft_strlcpy(new_word, word, ft_strlen(word));
	new_word[len] = c;
	new_word[len + 1] = 0;
	free(word);
	return (new_word);
}

void	get_name_of_file(t_request *cmd, char **word, char *s, int *i)
{
	skip_space(s , i);
    while (s[*i])
    {
        switch_quote(s[*i], &cmd->quote, i);
        if (!ft_strchr("|<> ", s[*i]) && !cmd->quote)
            *word = add_char_to_string(word, s[(*i)++]);
        else
            break ;
    }
	if (!word)
    {
        word = safe_malloc(1, sizeof(char));
        word[0] = 0;
    }
}
void	file_error(char *file_name, char *type_of_error);
{
	write(2, "minishell: ", 11);
	write(2, file_name, ft_strlen(file_name));
	write(2, ": ", 2);
	write(2, type_of_error, ft_strlen(type_of_error));
	write(2, "\n", 1);
}

int	check_access_of_file(char *file_name, int mode)
{
	if (access(file_name, mode))
	{
		if (mode)
			file_error(file_name, "Permission denied");
		else
			file_error(file_name, "No such file or directory");
		free_string(file_name);
		return (1);
	}
	return (0);
}

int	redirection_case(t_request *cmd, char *s, int *i)
{
	if (s[*i] == '<' && s[(*i) + 1] == '<')
		return (here_doc_case(cmd, i, s));
	else if (s[*i] == '<' && s[(*i) + 1] == '>')
		return (in_out_file_case());
	else if (s[*i] == '>' && s[(*i) + 1] == '>')
		return (append_case(cmd, i, s));
	else if (s[(*i) + 1] == '>')
		return (outfile_case(cmd, s, i));
	else if (s[(*i)] == '<')
		return (infile_case(cmd, s, i));
}

int infile_case(t_request *cmd,char *s, int *i);
{
    char *word;
	(*i)++;
    if (cmd->infile)
        close(cmd->infile);
    get_name_of_file(cmd, &word, s, i);
	if (check_access_of_file(word, EXIST))
		return (1);
    cmd->infile = open(word, O_RDONLY);
    if (cmd->infile < 0)
	{
        file_error(word, "Permission denied");
		free_string(word);
		return (1);
    }
	free_string(word);
	return (0);
}

int in_out_file_case(t_request *cmd, char *s, int *i)
{
	char *word;
	(*i) += 2;
	if (cmd->outfile != 1)
		close(cmd->outfile);
	get_name_of_file(cmd);
	cmd->outfile = open(word, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (cmd->outfile < 0)
	{
		if (check_access_of_file(word, EXIST))
			return (1);
		if (check_access_of_file(word, WRITE))
			return (1);
		if (check_access_of_file(word, READ))
			return (1);
	}
	free(word);
}

int outfile_case(t_request *cmd, char *s, int *i)
{
	char *word;
	(*i)++;
	if (cmd->outfile != 1)
		close(cmd->outfile);
	get_name_of_file(cmd, &word, s, i);
	if (check_access_of_file(word, WRITE))
	{
		free_string(word);
		return (1);
	}
	cmd->outfile = open(word, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (cmd->outfile < 0)
	{
		if (check_access_of_file(word, EXIST))
			return (1);
		if (check_access_of_file(word, WRITE))
			return (1);
	}
	free(word);
}

int	append_case(t_request *cmd, char *s, int *i)
{
	char *word;
	(*i) += 2;
	if (cmd->outfile != 1)
		close(cmd->outfile);
	get_name_of_file(cmd, &word, s, i);
	cmd->outfile = open(word, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (cmd->outfile < 0)
	{
		if (check_access_of_file(word, EXIST))
			return (1);
		if (check_access_of_file(word, WRITE))
			return (1);
	}
	free(word);
}

int	here_doc_case(t_request *cmd, int *i, char *s)
{
	char *word;
	(*i)++;
	if (cmd->infile)
		cmd->infile = 0;
	get_name_of_file(cmd, &word, s, i);
	cmd->here_doc = word;
	
}
