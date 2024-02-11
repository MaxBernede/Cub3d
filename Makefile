# Makefile for cub3d

# Variables
NAME	:= cub3D
LIBSA	:= ./libft/libft.a MLX42/build/libmlx42.a
INCLUDES := -I libft -I MLX42 -I includes

# Compiler and Flags
CC := gcc
CFLAGS := -g -fsanitize=address# -Wall -Wextra -Werror

ifeq ($(shell uname), Linux)
	MLX_FLAGS := -ldl -lglfw -pthread -lm
else
	MLX_FLAGS := -lglfw -L"/opt/homebrew/Cellar/glfw/3.3.8/lib" -framework Cocoa -framework OpenGL -framework IOKit
endif

# Directories and Files
OBJ_DIR := ./obj
SRC_DIR := ./src
HEADERS := libft/libft.h includes/cub3d.h includes/struct.h
SRC :=	main.c					\
		player.c				\
		valid_input.c			\
		parsing.c				\
		check_map.c				\
		rendering/render.c		\
		rendering/draw_wall.c	\
		rendering/draw_line.c	\
		rendering/dda.c			\
		utils/v2_operations.c	\
		utils/check_line.c 		\
		utils/clean.c			\
		utils/ft_atof.c			\
		utils/prints.c			\
		utils/utils.c			\
		utils/utils2.c			\
		utils/normalize.c		\
		utils/fix_angle.c		\
		fill_datas.c			\
		mlx/start.c				\
		mlx/hook.c				\
		map_parse.c				\
		gets.c					\
		flood_fill.c			\
		nodes.c					\
		nodes2.c				\

OBJ := $(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))
SRC := $(addprefix $(SRC_DIR)/,$(SRC))

# Targets
.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ)
	@echo $(Yellow) Building.. 🏠$(Color_Off)
	@make -C MLX42/build/
	@$(MAKE) -C libft bonus
	@$(CC) -Ofast -o $(NAME) -pg $^ $(LIBSA) $(CFLAGS) $(INCLUDES) $(MLX_FLAGS)
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
