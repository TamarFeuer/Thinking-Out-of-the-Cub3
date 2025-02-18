# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                            :+:    :+:            #
#                                                     +:+ +:+         +:+      #
#    By: rtorrent <rtorrent@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/09 20:52:16 by rtorrent          #+#    #+#              #
#    Updated: 2025/02/18 15:32:56 by rtorrent       ########   odam.nl         #
#                                                                              #
# **************************************************************************** #

# Tools and options:

CFLAGS += -Werror -Wextra -Wall

AR     := ar rcsv
RM     := rm -f

# **************************************************************************** #

# Filenames:

NAME   := libft.a

HEADER := libft.h

SRC    := ft_getnextline_fd.c\
	ft_snprintf.c\
	ft_strchr.c\
	ft_strrchr.c\
	ft_strncmp.c

OBJ    := $(SRC:.c=.o)

MKFILE := $(lastword $(MAKEFILE_LIST))

# **************************************************************************** #

# Primary targets:

all: $(NAME)

$(NAME):: $(MKFILE)
	@if [ -f "$@" ]; then $(MAKE) fclean; fi

$(NAME):: $(OBJ)
	$(AR) $@ $?

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re

# **************************************************************************** #

# Build prerequisites:

$(OBJ): $(HEADER)

ft_printf.o ft_getnextline_fd.o: %.o: %.h
