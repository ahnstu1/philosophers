# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hahn <hahn@student.42seoul.kr>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/01 07:33:30 by hahn              #+#    #+#              #
#    Updated: 2022/09/01 07:35:46 by hahn             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLGS = -Wall -Wextra -Werror

NAME = philo
OBJS = main.o \
		philo.o \
		philo_util.o \
		init.o \
		philo_act.o \
		check.o

all: $(NAME)

$(NAME): $(OBJS)
	cc $(OBJS) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: 
	make fclean
	make all

.PHONY: all clean fclean re