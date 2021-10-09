# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jalvarad <jalvarad@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/26 12:26:18 by jalvarad          #+#    #+#              #
#    Updated: 2021/10/09 13:03:34 by jalvarad         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= philo

CFLAGS	= -Wall -Werror -Wextra

SRCS	= philo.c \
			utils.c \
			error_management.c \
			parser_utils.c \
			prints.c

OBJS	= $(SRCS:.c=.o)

CC		= gcc

all: $(NAME)

$(NAME): $(OBJS) philo.h Makefile
		$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -lpthread

san: $(OBJS) philo.h Makefile
	$(CC) $(CFLAGS) -fsanitize=address $(OBJS) -o $(NAME) -lpthread

$(OBJS): $(SRCS) philo.h
		$(CC) $(CFLAGS) -c $(SRCS)

clean:
		rm -rf $(OBJS)

fclean: clean
		rm -rf $(NAME)

re: fclean all

.PHONY: all re clean fclean