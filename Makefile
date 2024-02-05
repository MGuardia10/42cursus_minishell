# NAME
NAME		=	minishell

# LIBFT
LIBFT		=	libft/libft.a
# SOURCE
SRC_DIR		=	src/
SRC_FILES	=	main.c \
				builtins.c
SRC			=	$(addprefix $(SRC_DIR), $(SRC_FILES))

# OBJECTS
OBJ_DIR		=	objs/
OBJ_FILES	=	$(SRC:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

# COMPILER
CC			=	cc
FLAGS		=	-Wall -Wextra -Werror
INCLUDE		=	-I inc
RM			=	rm -rf

# COLORS
RED		=		\033[91;1m
GREEN	=		\033[92;1m
YELLOW	=		\033[93;1m
BLUE	=		\033[94;1m
PINK	=		\033[95;1m
CLEAR	=		\033[0m

# RULES
all:	$(NAME)

$(NAME):	$(OBJ_FILES)
	@echo "\n$(BLUE)Compiling libft.$(CLEAR)"
	@make -sC libft
	@echo "$(GREEN)[libft --> OK]$(CLEAR)"
	@echo "$(BLUE)Compiling minishell program.$(CLEAR)"
	$(CC) $(FLAGS) $(LIBFT) $(OBJ_FILES) -o $(NAME)
	@echo "$(GREEN)[minishell --> OK]\n$(CLEAR)$(GREEN)Success!$(CLEAR)\n"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(FLAGS) -c $< -o $@

clean:
	@echo "$(BLUE)Removing compiled files.$(CLEAR)"
	@make clean -sC libft
	$(RM) $(OBJ_DIR)
	@echo "$(GREEN)Object files removed correctly\n$(CLEAR)"

fclean: clean
	@echo "$(BLUE)Removing binary files.$(CLEAR)"
	@make fclean -sC libft
	$(RM) $(NAME)
	@echo "$(GREEN)Object files and binary removed correctly\n$(CLEAR)"

re: fclean all

.PHONY:	all clean fclean re
