# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ynieto-s <ynieto-s@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/20 20:22:45 by ynieto-s          #+#    #+#              #
#    Updated: 2025/07/16 15:57:49 by ynieto-s         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
SRC =	pipex.c \
		utils.c
BONUS_SRC = pipex_bonus.c\
			utils_bonus.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

bonus: $(OBJ) $(OBJ_BONUS)
	$(NAME) $(OBJ) $(OBJ_BONUS)

clean:
	rm -f $(OBJ) 

fclean: clean
	rm -f $(NAME)

re : fclean all

.PHONY : all, clean, fclean, re
