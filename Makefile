# Makefile for cub3d

# Variables
NAME	:= cub3D
LIBSA	:= ./libft/libft.a MLX42/build/libmlx42.a
INCLUDES := -I libft -I MLX42 -I includes

# Compiler and Flags
CC := gcc
CFLAGS := -g -fsanitize=address# -Wall -Wextra -Werror
MACOS := -lglfw -L"/opt/homebrew/Cellar/glfw/3.3.8/lib" -framework Cocoa -framework OpenGL -framework IOKit

# Directories and Files
OBJ_DIR := ./obj
SRC_DIR := ./src
HEADERS := libft/libft.h includes/cub3d.h includes/struct.h
SRC :=	main.c			\
		valid_input.c	\
		parsing.c		\
		check_map.c		\
		utils/check_line.c 	\
		utils/clean.c	\
		utils/ft_atof.c		\
		utils/is_color.c	\
		utils/prints.c		\
		utils/to.c			\
		utils/utils.c	\
		mlx/start.c		\
		mlx/hook.c			\
		map_parse.c			\
		nodes.c				\

OBJ := $(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))
SRC := $(addprefix $(SRC_DIR)/,$(SRC))

# Targets
.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ)
	@echo $(Yellow) Building.. 🏠$(Color_Off)
	@make -C MLX42/build
	@$(MAKE) -C libft bonus
	@$(CC) -o $(NAME) $^ $(LIBSA) $(CFLAGS) $(INCLUDES) $(MACOS)
	@echo $(Green) Complete ✅ $(Color_Off)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS) | $(OBJ_DIR)
	@mkdir -p $(@D)
	@echo $(Purple) Compiling.. 🧱 $< $(Color_Off)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR):
	@mkdir $@

clean:
	@echo $(Cyan) Sweeping.. 💥 $(Color_Off)
	@$(MAKE) -C libft clean
	@rm -rf $(OBJ_DIR)

fclean: clean
	@echo $(Red) Thorough sweeping.. 💥 $(Color_Off)
	@$(MAKE) -C MLX42/build clean
	@$(MAKE) -C libft fclean
	@rm -f $(NAME)

re: fclean all

# Color Codes
Color_Off = "\033[0m"
Yellow = "\033[0;33m"
Purple = "\033[0;35m"
Cyan = "\033[0;36m"
Green = "\033[0;32m"
Red = "\033[0;31m"
