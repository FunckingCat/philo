# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: unix <unix@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/08 14:23:43 by unix              #+#    #+#              #
#    Updated: 2021/12/30 14:44:27 by unix             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = gcc
FLAGS = 
#FLAGS = -Wall -Werror -Wextra
LIB = -lpthread

HEADER = philo.h

MAIN_FILES = main.c utils.c exit.c init.c

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
	./philo 3 400 100 100

ttt: all
	./philo 3 400 100 100 5

.PHONY: all clean fclean re bonus