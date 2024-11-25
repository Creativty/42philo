# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aindjare <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/06 09:45:16 by aindjare          #+#    #+#              #
#    Updated: 2024/11/25 09:33:39 by aindjare         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			:=	cc
CFLAGS		:=	-Wall -Wextra -Werror
RM			:=	rm -rf
        	
NAME		:=	philo
SOURCES		:=	$(wildcard *.c)
OBJECTS		:=	$(SOURCES:%.c=%.o)
PARAM_PHILO	:=	50 300 100 50

all: $(NAME)

$(NAME): $(OBJECTS)
	$(CC) $(CFLAGS) -pthread -o $@ $^

debug: CFLAGS += -g
debug: re
	valgrind ./$(NAME) $(PARAM_PHILO)

sanitize: CFLAGS += -g -fsanitize=thread
sanitize: re
	./$(NAME) $(PARAM_PHILO)

test: all
	./$(NAME) $(PARAM_PHILO)

clean:
	$(RM) $(OBJECTS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re

.SECONDARY: $(OBJECTS)
