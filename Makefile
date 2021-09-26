# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jalvarad <jalvarad@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/26 12:26:18 by jalvarad          #+#    #+#              #
#    Updated: 2021/09/26 16:39:26 by jalvarad         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= philo

CFLAGS	= -Wall -Werror -Wextra #-fsanitize=address

SRCS	= philo.c \
			utils.c

OBJS	= $(SRCS:.c=.o)

CC		= gcc

all: $(NAME)

$(NAME): $(OBJS) philo.h
		$(CC) $(CFLAGS) $(OBJS) -o $(NAME) 
$(OBJS): $(SRCS)
		$(CC) $(CFLAGS) -c $(SRCS)

clean:
		rm -rf $(OBJS)

fclean: clean
		rm -rf $(NAME)

re: fclean all

.PHONY: all re clean fclean