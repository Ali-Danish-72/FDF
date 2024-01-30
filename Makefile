###############################################################################
#                                  VARIABLES                                  #
###############################################################################
NAME = fdf
CC = cc
CFLAGS = -Wall -Werror -Wextra
RESET=\033[0m
RED=\033[1;31m
GREEN=\033[1;32m
BLUE=\033[1;34m
CYAN=\033[1;36m
LIBFT_DIR = ./libft/
LIBFT = $(LIBFT_DIR)libft.a
MLX_DIR = ./minilibx/
MLX = $(MLX_DIR)libmlx.a
HEADERS = ./
SRCS_DIR = ./sources/
SRCS =	fdf.c hooks.c parsing.c projections.c window.c
SRCS_PATH = $(addprefix $(SRCS_DIR), $(SRCS))
OBJS_DIR = ./objects/
OBJS = $(SRCS:%.c=%.o)
OBJS_PATH = $(addprefix $(OBJS_DIR), $(OBJS))

###############################################################################
#                                     RULES                                   #
###############################################################################

all: $(NAME)

$(NAME): $(OBJS_DIR) $(OBJS_PATH)
	@make -s -C $(MLX_DIR)
	@make -s -C $(LIBFT_DIR) converters gnl printf memory strings
	@$(CC) $(CFLAGS) -framework OpenGL -framework AppKit $(OBJS_PATH) $(LIBFT) $(MLX) -o $(NAME)
	@echo "$(BLUE)PROGRAM $(GREEN)CREATED: $(CYAN)fdf$(RESET)"

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)

$(OBJS_PATH): $(SRCS_PATH)
	@make -s $(OBJS)

$(OBJS):
	@$(CC) $(CFLAGS) -c -I $(HEADERS) $(SRCS_DIR)$(@:%.o=%.c) -o $(OBJS_DIR)$@

clean:
	@make -s -C $(LIBFT_DIR) fclean
	@make -s -C $(MLX_DIR) clean
	@rm -rf $(OBJS_DIR)

fclean: clean
	@rm -f $(NAME)
	@echo "$(BLUE)PROGRAM $(RED)DESTROYED: $(CYAN)fdf$(RESET)"

re: fclean all

.PHONY: all clean fclean re