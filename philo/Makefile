# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abderrahim <marvin@42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/01 18:51:19 by abderrahim        #+#    #+#              #
#    Updated: 2024/12/01 19:36:23 by abderrahim       ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		:=	cc
CFLAGS	:=	-Wall -Wextra -Werror -g
LDFLAGS	:=	-pthread

NAME	:=	philo
SOURCES	:=	$(wildcard *.c)
OBJECTS	:=	$(SOURCES:%.c=%.o)

all: $(NAME)

segv: LDFLAGS += -fsanitize=address
segv: re

$(NAME): $(OBJECTS)

clean:
	$(RM) $(OBJECTS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re

.SECONDARY: $(OBJECTS)
