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

SHELL := /bin/bash

CC = clang++

FLAGS = -Wall -Wextra -Werror -std=c++98

SRC = main.cpp

OBJ = $(SRC:.cpp=.o)

HEADERS = -I ./include

all: STD FT

	@echo "execute std test"
	@./exestd 100 > tmp_std
	
	@echo "execute ft test"
	@./exeft 100 > tmp_ft
	
	@rm exeft exestd

	@diff tmp_ft tmp_std > tmp_diff 

	@echo -n "DIFF: "
	@if [ ! -s tmp_diff ]; then echo -e "\033[1;32m" "OK" "\033[0;37m"; else cat tmp_diff; fi
	

STD: $(SRC)
	$(CC) $(FLAGS) $(HEADERS) -D NAMESPACE=std -o exestd $(SRC)

FT: $(SRC)
	$(CC) $(FLAGS) $(HEADERS) -D NAMESPACE=ft -o exeft $(SRC)

clean:
	rm -rf tmp_ft tmp_std tmp_diff
	rm -rf $(OBJ)

fclean: clean 

re: fclean all
