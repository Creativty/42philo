# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aindjare <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/07 17:40:26 by aindjare          #+#    #+#              #
#    Updated: 2024/11/17 18:02:43 by aindjare         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

RM		:=	rm -rf

CC		:=	cc
CFLAGS	:=	-Wall -Wextra -Werror -O0

NAME	:=	philo
OBJECTS	:=	main.o alloc.o time.o parameters.o mutex.o person.o people.o

all: $(NAME)

debug: CFLAGS += -g
debug: re
	valgrind ./$(NAME) 5 300 100 100

sanitize: CFLAGS += -g -fsanitize=thread
sanitize: re
	./$(NAME) 5 300 100 100

$(NAME): $(OBJECTS)
	$(CC) $(CFLAGS) -pthread $^ -o $@

clean:
	$(RM) $(OBJECTS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re

.SECONDARY: $(OBJECTS)
