###############################################################################
#                                  VARIABLES                                  #
###############################################################################
NAME = libft.a
CC = cc
CFLAGS = -Wall -Werror -Wextra -g3
RESET=\033[0m
BLACK=\033[1;30m
RED=\033[1;31m
GREEN=\033[1;32m
YELLOW=\033[1;33m
BLUE=\033[1;34m
MAGENTA=\033[1;35m
CYAN=\033[1;36m
WHITE=\033[1;37m
OBJS = \
	$(CONVERTERS_OBJS) \
	$(GNL_OBJS) \
	$(MEMORY_OBJS) \
	$(PRINTF_OBJS) \
	$(STRINGS_OBJS)
HEAD = ./
SRC_PATH = ./srcs/

all: $(NAME)

###############################################################################
#                                  CONVERTERS                                 #
###############################################################################
CONVERTERS_DIR = $(SRC_PATH)converters/
CONVERTERS_FILES = ft_atoi.c
CONVERTERS_SRCS = $(addprefix $(CONVERTERS_DIR), $(CONVERTERS_FILES))
CONVERTERS_OBJS = $(CONVERTERS_SRCS:.c=.o)

$(CONVERTERS_OBJS): %.o: %.c
	@if ! $(CC) $(CFLAGS) -c -I $(HEAD) $< -o $@; then \
	echo "$(YELLOW)ERROR WHILE COMPILING THE CONVERTERS FUNCTIONS!!!$(RESET)"; \
	fi

###############################################################################
#                                GET NEXT LINE                                #
###############################################################################
GNL_DIR = $(SRC_PATH)gnl/
GNL_FILES = \
		get_next_line.c
GNL_SRCS = $(addprefix $(GNL_DIR), $(GNL_FILES))
GNL_OBJS = $(GNL_SRCS:.c=.o)

$(GNL_OBJS): %.o: %.c
	@if ! $(CC) $(CFLAGS) -c -I $(HEAD) $< -o $@; then \
	echo "$(YELLOW)ERROR WHILE COMPILING THE GET_NEXT_LINE FUNCTION!!!$(RESET)"; \
	fi

###############################################################################
#                                   MEMORY                                    #
###############################################################################
MEMORY_DIR = $(SRC_PATH)memory/
MEMORY_FILES = ft_calloc.c
MEMORY_SRCS = $(addprefix $(MEMORY_DIR), $(MEMORY_FILES))
MEMORY_OBJS = $(MEMORY_SRCS:.c=.o)

$(MEMORY_OBJS): %.o: %.c
	@if ! $(CC) $(CFLAGS) -c -I $(HEAD) $< -o $@; then \
	echo "$(YELLOW)ERROR WHILE COMPILING THE MEMORY FUNCTIONS!!!$(RESET)"; \
	fi

###############################################################################
#                                   PRINTF                                    #
###############################################################################
PRINTF_DIR = $(SRC_PATH)printf/
PRINTF_FILES = \
		address_print.c \
		char_print.c \
		ft_printf.c \
		hexa_print.c \
		num_print.c \
		str_print.c \
		unsigned_base_print.c
PRINTF_SRCS = $(addprefix $(PRINTF_DIR), $(PRINTF_FILES))
PRINTF_OBJS = $(PRINTF_SRCS:.c=.o)

$(PRINTF_OBJS): %.o: %.c
	@if ! $(CC) $(CFLAGS) -c -I $(HEAD) $< -o $@; then \
	echo "$(YELLOW)ERROR WHILE COMPILING THE PRINTF FUNCTION!!!$(RESET)"; \
	fi

###############################################################################
#                                  STRINGS                                    #
###############################################################################
STRINGS_DIR = $(SRC_PATH)strings/
STRINGS_FILES = \
		ft_split.c \
		ft_strchr.c \
		ft_strjoin.c \
		ft_strlcpy.c \
		ft_strlen.c \
		ft_strncmp.c \
		ft_substr.c
STRINGS_SRCS = $(addprefix $(STRINGS_DIR), $(STRINGS_FILES))
STRINGS_OBJS = $(STRINGS_SRCS:.c=.o)

$(STRINGS_OBJS): %.o: %.c
	@if ! $(CC) $(CFLAGS) -c -I $(HEAD) $< -o $@; then \
	echo "$(YELLOW)ERROR WHILE COMPILING THE STRING FUNCTIONS!!!$(RESET)"; \
	fi

###############################################################################
#                                  COMPLETE                                   #
###############################################################################
$(NAME): $(OBJS)
	@ar rcs $(NAME) $(OBJS)
	@echo "$(BLUE)ARCHIVE $(GREEN)CREATED: $(CYAN)libft.a$(RESET)"

clean:
	@rm -f $(OBJS)
	@echo "$(BLUE)OBJECTS $(RED)DESTROYED$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(BLUE)ARCHIVE $(RED)DESTROYED: $(CYAN)libft.a$(RESET)"

re: fclean all

.PHONY: all clean fclean re
