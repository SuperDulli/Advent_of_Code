# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: chelmerd <chelmerd@student.wolfsburg.de    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/03 10:55:50 by chelmerd          #+#    #+#              #
#    Updated: 2021/12/14 14:02:17 by chelmerd         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
BUFFER_SIZE = 10
CFLAGS = -Wall -Wextra -Werror -g
NAME = polymer
SRCS = $(NAME).c

LIBFT_FOLDER= ../utils/libft
LIBFT_NAME	= libft.a
GNL_FOLDER	= ../utils/gnl
GNL_SRCS	= $(GNL_FOLDER)/get_next_line.c $(GNL_FOLDER)/get_next_line_utils.c

OBJS		= $(patsubst %.c, %.o, $(SRCS))
GNL_OBJS	= get_next_line.o get_next_line_utils.o

$(NAME): $(NAME).o $(GNL_OBJS) makelib
	$(CC) -o $@ $< $(GNL_OBJS) $(LIBFT_FOLDER)/$(LIBFT_NAME)

all: $(NAME)

run: all
	./$(NAME)

makelib:
	make -C $(LIBFT_FOLDER)
	make bonus -C $(LIBFT_FOLDER)

$(GNL_OBJS): $(GNL_SRCS) $(GNL_FOLDER)/get_next_line.h
	$(CC) $(CFLAGS) -D BUFFER_SIZE=$(BUFFER_SIZE) -c $(GNL_SRCS)

%.o: %.c
	$(CC) -c $(CFLAGS) -o $@ $< -I$(LIBFT_FOLDER)

clean:
	rm -f *.o

fclean: clean
	rm -f $(NAME)
	make fclean -C $(LIBFT_FOLDER)

re: fclean all

.PHONY: all clean fclean re
