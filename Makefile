# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tfeuer <tfeuer@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/01 20:19:25 by rtorrent          #+#    #+#              #
#    Updated: 2025/04/06 14:12:58 by tfeuer           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror -g -Ilibs/MLX42/include/MLX42
LDFLAGS = -ldl -lglfw -pthread -lm

NAME = cub3D

HDR = inc/game.h

SRC = src/clean.c \
	src/color.c \
	src/flood_fill_map.c \
	src/hooks.c \
	src/horizontal.c \
	src/init.c \
	src/intersections.c \
	src/lexer.c \
	src/line.c \
	src/main.c \
	src/map_parser.c \
	src/mmap.c \
	src/mous3.c \
	src/parser.c \
	src/perspective_scene.c \
	src/player.c \
	src/rays.c \
	src/stats.c \
	src/utils.c \
	src/vertical.c

OBJ_DIR = obj
OBJ = $(SRC:src/%.c=$(OBJ_DIR)/%.o)

LIBFT_DIR = libs/libft
MLX_DIR = libs/MLX42
LIB_MLX = $(MLX_DIR)/build/libmlx42.a
LIBFT = $(LIBFT_DIR)/libft.a

.PHONY: all clean fclean re

all: $(NAME)

$(NAME)::
	@make -s -C $(LIBFT_DIR)

$(NAME):: $(LIB_MLX) $(LIBFT) $(OBJ)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT) $(LIB_MLX) $(LDFLAGS)
	@echo "$(DGREEN)Finished building $@!$(RESET)"
	
$(OBJ_DIR)/%.o: src/%.c $(HDR)
	@mkdir -p $(dir $@)  # Ensure the directory for the object file exists
	@echo "$(TEAL)Compiling $@ from $<...$(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@

$(addprefix $(OBJ_DIR)/,lexer.o parser.o map_parser.o): src/lexer_parser.h

$(LIB_MLX):
	@cmake $(MLX_DIR) -B $(MLX_DIR)/build
	@cmake --build $(MLX_DIR)/build -j4

clean:
	@make -C $(LIBFT_DIR) clean >/dev/null
	@echo "$(PINK)Cleaning $(OBJ)!$(RESET)"
	@rm -rf $(OBJ_DIR)

fclean: clean
	@make -C $(LIBFT_DIR) fclean >/dev/null
	@rm -rf $(MLX_DIR)/build
	@echo "$(CYAN)Removing MLX build!$(RESET)"
	@echo "$(CYAN)Cleaning $(NAME)!$(RESET)"
	@rm -f $(NAME)

re: fclean all

TEAL	= \033[38;5;30m
CYAN	= \033[38;2;0;255;255m
PINK	= \033[1;35m
DGREEN	= \033[38;5;22m
RESET	= \033[0m
