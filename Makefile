NAME = minishell

all: $(NAME)

$(NAME):
	gcc commands_2.c commands_1.c main.c -lreadline -o $(NAME)
clean:
	rm -f *.o
fclean:
	make clean
	rm -f $(NAME)