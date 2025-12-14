# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: waragwon <waragwon@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/23 14:07:23 by waroonwork@       #+#    #+#              #
#    Updated: 2025/12/14 19:02:04 by waragwon         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			:=	philo

CC				:=	cc
CFLAG			:=	-Wall -Wextra -Werror -g3 -pthread -fsanitize=thread

INC_DIR			:=	includes/
SRCS_DIR		:=	srcs/

SRCS_FILES		:=	main.c \
					utils/utils1.c \
					philo/init.c philo/life.c philo/life_utils.c

SRCS			:=	$(SRCS_FILES:%.c=$(SRCS_DIR)%.c)
OBJS			:=	$(SRCS:%.c=%.o)

all				:	$(NAME)

$(NAME)			:	$(OBJS)	Makefile
	$(CC) $(CFLAG) -I$(INC_DIR) $(OBJS) -o $(NAME)

%.o				:	%.c
	$(CC) $(CFLAG) -I$(INC_DIR) -c $< -o $@

clean			:
	rm -rf $(OBJS)

fclean			:	clean
	rm -rf $(NAME)

re				:	fclean all

.PHONY			:	all clean fclean re