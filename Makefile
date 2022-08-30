CFLGS = -Wall -Wextra -Werror

NAME = philo
OBJS = main.o \
		philo.o \
		philo_util.o \
		init.o

all: $(NAME)

$(NAME): $(OBJS)
	cc $(OBJS) -o $(NAME) -g -fsanitize=address

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re