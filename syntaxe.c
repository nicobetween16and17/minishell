
int	iswhite_space(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

void check_beginning(char *s, int *i)
{
	skip_space(&s);
	if (ft_strchr("|()", s[(*i)]))
	{
		printf("probleme de syntaxe");
		return (1);
	}
	return (0);

}

int check_left(char *s)
{
	if (*s == '>')
	{
		skip_space(&s);
		if (ft_strchr("<>|">>, s))
			return (erreur_de_syntaxe());
		return (0);
	}
	skip_space(&s);
	if (ft_strchr("<>|", s))
		return (erreur_de_syntaxe());	
	return (0);
}

int check_right(char *s)
{
	if (*s == '>')
		skip_space(s);
		if (ft_strchr("<>|"))
			error_message("probleme de syntaxe");
	if (ft_strchr("<>", *s))
	{
		skip_space(&s);
		if (ft_strchr("<>|", s))
			return (erreur_de_syntaxe());
		return (0);
	}
	skip_space(&s);
	if (ft_strchr("<>|", s))
		return (erreur_de_syntaxe());
	return (0);
}

int	check_syntaxe_redirection(char **s)
{
	if (*s == '>')
		return (check_left(s));
	if (*s == '<')
		return (check_right(s));
	return (0);
	
}

int	check_pipe_after_pipe(char **s)
{
	while (is_white_space(**s))
		s++;
	if (*s == '|')
		return (1);
	return (0);
}

int	check_syntax(char *s)
{
	int i = -1;
	char quote;

	quote = 0;
	check_beginning(s, &i);
	while (*s)
	{
		switch_quote(s, quote);
		if (!quote && ft_strchr("&()", *s))
			error_message("probleme de syntaxe");
		check_syntaxe_redirection(&s);
		if (*s == '|' && check_pipe_after_pipe())
			error_message("probleme de syntaxe");
		s++;
	}
	if (quote)
		error_message("quote non ferme");
	return (0);
}

int	erreur_de_syntaxe()
{
	printf("erreur de syntaxe");
	return (1);
}
