# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ynieto-s <ynieto-s@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/20 20:22:45 by ynieto-s          #+#    #+#              #
#    Updated: 2025/07/11 16:36:54 by ynieto-s         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
SRC =	cost.c \
		ft_split.c \
		main.c \
		moves.c \
		operations.c \
		position.c \
		push.c \
		r_both.c \
		reverse.c \
		rotate.c \
		sort.c \
		swap.c \
		utils.c \
		lists_utils.c
		
OBJ = $(SRC:.c=.o)

AR = ar rcs

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) 

fclean: clean
	rm -f $(NAME)

re : fclean all

.PHONY : all, clean, fclean, re
