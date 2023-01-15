#include "minishl.h"


void    switch_quote(char c, char *quote, int *i)
{
    if (!ft_strchr("\"'", c))
        return ;
    if (c == *quote)
        *quote = 0;
    if (!(*quote))
    {
        *quote = c;
        (*i)++;
    }
    return ;
}

void	redirection_case(t_request *cmd, char *s, int *i)
{
	if (s[*i] == '<' && s[(*i) + 1] == '<')
	{
		here_doc_case(cmd, i, s);
	}
	else if (s[*i] == '<' && s[(*i) + 1] == '>')
	{
		in_out_file_case();
	}
	else if (s[*i] == '>' && s[(*i) + 1] == '>')
	{
		append_case();
	}
	else if (s[(*i) + 1] == '>')
	{
		outfile_case(cmd, s, i);
	}
	else if (s[(*i)] == '<')
	{
		infile_case();
}

void infile_case(t_request *cmd,char *s, int *i);
{
    char *word;
    if (cmd->infile)
        close(cmd->infile);
    while(iswhite_space(s[(*i)]))
        (*i)++;
    while (s[*i])
    {
        switch_quote(s[*i], &cmd->quote, i);
        if (!ft_strchr("|<> ", s[*i]) && !cmd->quote)
            word = add_char_to_string(word, s[(*i)++])
        else
            break ;
    }
    if (!word)
    {
        word = safe_malloc(1, sizeof(char));
        word[0] = 0;
    }
    cmd->infile = open(word, O_RDONLY);
    if (cmd->infile < 0)
        error_message("file_not_found");
    free(word);

}

void in_out_file_case(t_request *cmd, char *s, int *i)
{
	char *word;
	(*i)++;
	if (cmd->outfile != 1)
		close(cmd->outfile);
	while (iswhite_space(s[(*i)]))
		(*i)++;
	while (s[(*i)])
	{
		make_the_switch(sq);
        if (ft_strchr("|<> ", s[*i]))
		word = add_char_to_string(word, s[(*i)]);
		++(*i);
	}
	if(!word)
	{
		word = b_malloc(1 * sizeof(char));
		word[0] = 0;
	}
	if (check_access_of_file(word, READ))
	{
		free(word):
		return (0);
	}
	cmd->outfile = open(word, O_CREAT | O_WRONLY | O_APPEND, 0644);
	free(word);
	if (cmd->outfile < 0)
		return (file_error());
}

void outfile_case(t_command *cmd, char *s, int *i)
{
	char *word;
	if (cmd->outfile != 1)
		close(cmd->outfile);
	while (iswhite_space(s[++(*i)]))
		(*i)++;
	while (s[(*i)] && s[(*i)] != '"|" '&& (!iswhite_space(s[(*i)])
		|| (iswhite_space(s[(*i)]) && in_quote(sq))))
	{
		make_the_switch(sq);
		redirection_case(cmd, s, &(*i));
		if (s[(*i)] != '\'' && s[(*i)] != '\"' )
			word = add_char_to_string(word, s[(*i)]);
			(*i)++;
	}
	if(!word)
	{
		word = b_malloc(1 * sizeof(char));
		word[0] = 0;
	}
	if (check_access_of_file(word, READ))
	{
		free(word);
		return (0);
	}
	cmd->outfile = open(word, O_CREAT | O_WRONLY | O_APPEND, 0644);
	free(word);
	if (cmd->outfile < 0)
		return (file_error());
}

void	append_case(t_command *cmd, char *s, int *i)
{
	char *word;
	if (cmd->outfile != 1)
		close(cmd->outfile);
	while (iswhite_space(s[++(*i)]))
		(*i)++;
	while (s[++(*i)] && s[(*i)] != '"|" '&& (!iswhite_space(s[(*i)])
		|| (iswhite_space(s[(*i)]) && in_quote(sq))))
	{
		make_the_switch(sq);
		redirection_case(cmd, s, &(*i));
		if (s[(*i)] != '\'' && s[(*i)] != '\"' )
			word = add_char_to_string(word, s[(*i)]);
	}
	if(!word)
	{
		word = b_malloc(1 * sizeof(char));
		word[0] = 0;
	}
	if (check_access_of_file(word, READ))
	{
		free(word);
		return (0);
	}
	cmd->outfile = open(word, O_CREAT | O_WRONLY | O_APPEND, 0644);
	free(word);
	if (cmd->outfile < 0)
		return (file_error());
}

void	here_doc_case(t_command *cmd, int *i, char *s)
{
	t_switch_quote sq;
	char *word;
	init_switch_quote(sq);
	(*i)++;
	if (cmd->infile)
		cmd->infile = 0;
	while (iswhite_space(s[++(*i)]))
		(*i)++;
	while (s[++(*i)] && s[(*i)] != '"|" '&& (!iswhite_space(s[(*i)])
		|| (iswhite_space(s[(*i)]) && in_quote(sq))))
	{
		switch_quote(s[*i], &cmd->quote, i);
		if (s[(*i)] != '\'' && s[(*i)] != '\"' )
			word = add_char_to_string(word, s[(*i)]);
	}
	if (word)
		cmd->here_doc = word;
	else
	{
		cmd->here_doc = b_malloc(1 * sizeof(char));
		cmd->here_doc[0] = 0;
	}
}