# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: unix <unix@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/08 14:23:43 by unix              #+#    #+#              #
#    Updated: 2022/01/05 12:49:40 by unix             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_bonus
CC = gcc
FLAGS = -Wall -Werror -Wextra
LIB = -lpthread

HEADER = philo.h

MAIN_FILES = main.c utils.c init.c philo.c

SRC = $(MAIN_FILES:.c=.o)

RM = rm -f

all: $(NAME)

%.o : %.c $(HEADER)
	$(CC) $(FLAGS) -c $< -o $@

$(NAME): $(SRC)
	$(CC) $(FLAGS) -o $(NAME) $(SRC) $(LIB)

clean:
	$(RM) $(SRC)

fclean: clean
	$(RM) $(NAME)

re: fclean all

tt: all
	./philo_bonus 4 310 200 100 

ttt: all
	./philo_bonus 5 500 150 100 10

.PHONY: all clean fclean re