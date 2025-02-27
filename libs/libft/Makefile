# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                            :+:    :+:            #
#                                                     +:+ +:+         +:+      #
#    By: rtorrent <rtorrent@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/09 20:52:16 by rtorrent          #+#    #+#              #
#    Updated: 2025/02/27 14:08:42 by rtorrent       ########   odam.nl         #
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

SRC    := ft_bzero.c\
	ft_calloc.c\
	ft_getnextline2.c\
	ft_isdigit.c\
	ft_isprint.c\
	ft_lstadd_back.c\
	ft_lstclear.c\
	ft_lstdelone.c\
	ft_lstlast.c\
	ft_lstnew.c\
	ft_memchr.c\
	ft_memcpy.c\
	ft_memmove.c\
	ft_memset.c\
	ft_snprintf.c\
	ft_strchr.c\
	ft_strcspn.c\
	ft_strdup.c\
	ft_strlcpy.c\
	ft_strlen.c\
	ft_strrchr.c\
	ft_strncmp.c\
	ft_strspn.c\
	ft_strtok.c\
	ft_strtok_r.c\
	ft_substr.c\
	xx_printf.c\
	xx_printf_read_specf.c

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

ft_getnextline2.o: ft_getnextline.h

ft_snprintf.o xx_printf.o xx_printf_read_specf.o: ft_printf.h
