# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aindjare <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/06 09:45:16 by aindjare          #+#    #+#              #
#    Updated: 2024/11/07 16:10:56 by aindjare         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			:=	cc
CFLAGS		:=	-Wall -Wextra -Werror
RM			:=	rm -rf
        	
NAME		:=	philo
SOURCES		:=	$(wildcard *.c)
OBJECTS		:=	$(SOURCES:%.c=%.o)
NAME_ARGS	:=	8 300 100 100

all: $(NAME)

$(NAME): $(OBJECTS)
	$(CC) $(CFLAGS) -pthread -o $@ $^

clean:
	$(RM) $(OBJECTS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

leaks: CFLAGS += -g
leaks: re
	valgrind ./$(NAME) $(NAME_ARGS)

sanitize: CFLAGS += -fsanitize=thread -g -O0
sanitize: re
	./$(NAME) $(NAME_ARGS)

.PHONY: all clean fclean re

.SECONDARY: $(OBJECTS)
