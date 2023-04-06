NAME			=	minishell

SRCDIR 			=	./

SRC				=   parse0.c parse1.c main.c pipe.c pipe2.c heredoc.c export.c export2.c sort_env.c env_node.c env_node2.c builtins.c utils.c utils2.c utils3.c fd.c signals.c redirect.c token.c dollar_signs.c env.c utils4.c

SRCS			=	$(addprefix $(SRCDIR), $(SRC))

OBJS			=	$(SRCS:.c=.o)

CC			= gcc

CFLAGS 	= -Wall -Werror -Wextra -I /Users/$(USER)/.brew/Cellar/readline/8.2.1/include

all:		$(NAME)

$(NAME):	$(SRCS) $(OBJS)
			@make -C libft bonus
			@$(CC) -lreadline libft/libft.a $(CFLAGS) -L /Users/$(USER)/.brew/Cellar/readline/8.2.1/lib  $(OBJS) -o $(NAME)

%.o:%.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
			@rm -f $(OBJS)

fclean:		clean
				@make -C libft fclean
				@rm -f $(NAME)

re:			fclean all
