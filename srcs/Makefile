NAME			=	minishell

SRCDIR 			=	./

SRC				=   parse0.c parse1.c main.c pipe.c echo.c pwd.c heredoc.c export.c cd.c libft/libft.a sort_env.c utils.c

SRCS			=	$(addprefix $(SRCDIR), $(SRC))

OBJS			=	$(SRCS:.c=.o)

CC			= gcc

CFLAGS 		= -Wall -Werror -Wextra

all:		$(NAME)

$(NAME):	$(SRCS) $(OBJS)
			@$(CC) -lreadline $(CFLAGS) $(OBJS) -o $(NAME)

%.o:%.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
			@rm -f $(OBJS)

fclean:		clean
			@rm -f $(NAME)

re:			fclean all