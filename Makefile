# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: unix <unix@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/08 14:23:43 by unix              #+#    #+#              #
#    Updated: 2021/12/29 14:19:02 by unix             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = gcc
FLAGS = 
#FLAGS = -Wall -Werror -Wextra
LIB = -lpthread

HEADER = philo.h

MAIN_FILES = main.c utils.c

SRC = $(MAIN_FILES:.c=.o)

RM = rm -f

all: $(NAME)

%.o : %.c $(HEADER)
	$(CC) $(FLAGS) -c $< -o $@

$(NAME): $(SRC)
	$(CC) $(FLAGS) $(LIB) -o $(NAME) $(SRC) 

clean:
	$(RM) $(SRC)

fclean: clean
	$(RM) $(NAME)

re: fclean all

tt: all
	./philo 3 400 50 100

ttt: all
	./philo 3 400 50 100 5

.PHONY: all clean fclean re bonus