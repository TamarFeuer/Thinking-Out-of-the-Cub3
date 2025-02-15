NAME = libft.a

FLAGS = -Wall -Wextra -Werror

INCLUDE_DIR = ./includes
HEADER = $(INCLUDE_DIR)/libft.h

SRC = $(shell find $(SRC_DIR) -iname "*.c")

SRC_DIR = sources
OBJ_DIR = objects

OBJECTS	:= $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

# ==================== RULES ====================

all: $(NAME)

$(NAME): $(OBJECTS) $(HEADER)
	ar rcs $(NAME) $(OBJECTS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	@printf "Building $@\n"
	@$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
