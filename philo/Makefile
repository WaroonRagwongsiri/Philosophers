# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: waroonwork@gmail.com <WaroonRagwongsiri    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/23 14:07:23 by waroonwork@       #+#    #+#              #
#    Updated: 2025/11/23 14:12:59 by waroonwork@      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			:=	philo

CC				:=	cc
CFLAG			:=	-Wall -Wextra -Werror -g3

INC_DIR			:=	includes/
SRCS_DIR		:=	srcs/

SRCS_FILES		:=	main.c \

SRCS			:=	$(SRCS_FILES:%.c=$(SRCS_DIR)%.c)
OBJS			:=	$(SRCS:%.c=%.o)

all				:	$(NAME)

$(NAME)			:	$(OBJS)
	$(CC) $(CFLAG) -I$(INC_DIR) $(OBJS) -o $(NAME)

%.o				:	%.c
	$(CC) $(CFLAG) -I$(INC_DIR) -c $< -o $@

clean			:
	rm -rf $(OBJS)

fclean			:	clean
	rm -rf $(NAME)

re				:	fclean all

.PHONY			:	all clean fclean re