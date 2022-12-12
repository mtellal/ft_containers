# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mtellal <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/15 10:03:06 by mtellal           #+#    #+#              #
#    Updated: 2022/12/12 11:51:31 by mtellal          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = clang++

FLAGS = -Wall -Wextra -Werror -std=c++98

NAME = containers

SRC = main.cpp

OBJ = $(SRC:.cpp=.o)

HEADERS = -I ./include

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) -o $(NAME) $(OBJ)

%.o:%.cpp
	$(CC) $(FLAGS) $(HEADERS) -o $@ -c $<

clean:
	rm -rf $(OBJ)

fclean: clean 
	rm -rf $(NAME)

re: fclean all
