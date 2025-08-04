# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ynieto-s <ynieto-s@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/20 20:22:45 by ynieto-s          #+#    #+#              #
#    Updated: 2025/08/04 14:25:34 by ynieto-s         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
BONUS_NAME = pipex_bonus
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
SRC =	pipex.c \
		path.c \
		tools.c \
		input_output.c \
		error_exit.c \
		ft_split.c \
		ft_strchr.c \
		ft_strjoin.c \
		ft_strlen.c \
		ft_strncmp.c \
		ft_strdup.c
		
BONUS_SRC = pipex_bonus.c\
			utils_bonus.c \
			tools.c \
			path.c \
			handle_process_bonus.c \
			heredoc_bonus.c \
			close_and_clean_bonus.c \
			error_exit.c \
			ft_split.c \
			ft_strchr.c \
			ft_strjoin.c \
			ft_strlen.c \
			ft_strncmp.c \
			ft_strdup.c \
			ft_substr.c

OBJ = $(SRC:.c=.o)
BONUS_OBJ = $(BONUS_SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

bonus: $(BONUS_NAME)

$(BONUS_NAME): $(BONUS_OBJ)
	$(CC) $(CFLAGS) $(BONUS_OBJ) -o $(BONUS_NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(BONUS_OBJ)

fclean: clean
	rm -f $(NAME) $(BONUS_NAME)

re : fclean all


.PHONY : all clean fclean re bonus
