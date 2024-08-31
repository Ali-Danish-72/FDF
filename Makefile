###############################################################################
#                                  VARIABLES                                  #
###############################################################################
NAME = fdf
CC = cc
CFLAGS = -Wall -Werror -Wextra -fsanitize=address -g3
RESET=\033[0m
RED=\033[1;31m
GREEN=\033[1;32m
BLUE=\033[1;34m
CYAN=\033[1;36m
LIBFT_DIR = libft/
LIBFT = $(LIBFT_DIR)libft.a
ifeq ($(shell uname -s), Darwin)
MLX_DIR = minilibx-mac/
MLX_FLAGS = -framework OpenGL -framework AppKit
endif
ifeq ($(shell uname -s), Linux)
MLX_DIR = minilibx-linux/
MLX_FLAGS = -Lmlx -lX11 -lXext -lm
endif
MLX = $(MLX_DIR)libmlx.a
HEADERS = ./
SRCS_DIR = sources/
SRCS =	fdf.c hooks.c parsing.c projections.c window.c
SRCS_PATH = $(addprefix $(SRCS_DIR), $(SRCS))
OBJS_DIR = objects/
OBJS = $(SRCS:%.c=%.o)
OBJS_PATH = $(addprefix $(OBJS_DIR), $(OBJS))

###############################################################################
#                                     RULES                                   #
###############################################################################

all: $(NAME)

$(NAME): $(OBJS_DIR) $(OBJS_PATH) $(MLX) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJS_PATH) $(MLX_FLAGS) -o $(NAME) $(LIBFT) $(MLX)
	@echo "$(BLUE)OBJECTS $(GREEN)CREATED$(RESET)"
	@echo "$(BLUE)PROGRAM $(GREEN)CREATED: $(CYAN)fdf$(RESET)"

$(MLX):
	@make -s -C $(MLX_DIR)
	@echo "$(BLUE)ARCHIVE $(GREEN)CREATED: $(CYAN)libmlx.a$(RESET)"

$(LIBFT):
	@make -s -C $(LIBFT_DIR)

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)

$(OBJS_PATH): $(SRCS_PATH)
	@make -s $(OBJS)

$(OBJS):
	@$(CC) $(CFLAGS) -c $(SRCS_DIR)$(@:%.o=%.c) -o $(OBJS_DIR)$@

clean:
	@make -s -C $(MLX_DIR) clean
	@echo "$(BLUE)ARCHIVE $(RED)DESTROYED: $(CYAN)libmlx.a$(RESET)"
	@rm -rf $(OBJS_DIR)
	@make -s -C $(LIBFT_DIR) fclean

fclean: clean
	@rm -f $(NAME)
	@echo "$(BLUE)PROGRAM $(RED)DESTROYED: $(CYAN)fdf$(RESET)"

re: fclean all

.PHONY: all clean fclean re