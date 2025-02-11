CC = cc
# CFLAGS = -Wall -Wextra -Werror -Isrc -Ilibs/libft -Ilibs/MLX42/include/MLX42 -g -fsanitize=address -O3
# CFLAGS = -Wall -Wextra -Werror -Isrc -Ilibs/MLX42/include/MLX42 -g -fsanitize=address -O3
#CFLAGS = -Wall -Wextra -Werror -Isrc -g -Ilibs/MLX42/include/MLX42
CFLAGS = -Wall -Wextra -Werror -g -Ilibs/MLX42/include/MLX42
LDFLAGS = -ldl -lglfw -pthread -lm

NAME = cub3D

SRC =	src/main.c src/line_algorithm.c src/mmap.c src/player.c src/hooks.c src/clean.c \
		src/stats.c src/libft.c src/color.c src/rays.c src/intersections.c src/draw_scene.c \
		src/utils.c src/init.c src/horizontal.c src/vertical.c \
		src/parsing/parsing.c src/parsing/parse_identifiers.c \
		src/parsing/parse_map.c src/parsing/parsing_utils.c src/parsing/check_map.c \
		src/parsing/has_surrounding_walls.c src/parsing/clean_and_exit.c \
		src/gnl/gnl.c src/gnl/gnl_utils.c \
		

OBJ_DIR = obj
OBJ = $(SRC:src/%.c=$(OBJ_DIR)/%.o)

LIBFT_DIR = libs/libft
MLX_DIR = libs/MLX42
LIB_MLX = $(MLX_DIR)/build/libmlx42.a
LIBFT = $(LIBFT_DIR)/libft.a

.PHONY: all clean fclean re

all: $(NAME)


#(NAME): $(OBJ) $(LIBFT) $(LIB_MLX)
$(NAME): $(LIB_MLX) $(LIBFT) $(OBJ)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT) $(LIB_MLX) $(LDFLAGS)
#	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIB_MLX) $(LDFLAGS)
	@echo "$(DGREEN)Finished building $@!$(RESET)"

$(OBJ_DIR)/%.o: src/%.c
	@mkdir -p $(dir $@)  # Ensure the directory for the object file exists
	@echo "$(TEAL)Compiling $@ from $^...$(RESET)"
	@$(CC) $(CFLAGS) -c -o $@ $^

 $(LIBFT):
	@make -C $(LIBFT_DIR)

$(LIB_MLX):
	@cmake $(MLX_DIR) -B $(MLX_DIR)/build
	@make -C $(MLX_DIR)/build -j4
	
clean:
	@make -C $(LIBFT_DIR) clean >/dev/null
	@echo "$(PINK)Cleaning $(OBJ)!$(RESET)"
	@rm -rf $(OBJ_DIR)

fclean: clean
	@make -C $(LIBFT_DIR) fclean >/dev/null
	@echo "$(CYAN)Cleaning $(NAME)!$(RESET)"
	@rm -f $(NAME)

re: fclean all

TEAL	= \033[38;5;30m
CYAN	= \033[38;2;0;255;255m
PINK	= \033[1;35m
DGREEN	= \033[38;5;22m
RESET	= \033[0m