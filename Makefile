# NAME
NAME		=	minishell

# LIBFT
LIBFT		=	libft/libft.a

# SOURCE
SRC_DIR		=	src/
SRC_FILES	=	main.c
# SRC_FILES	=	main2.c
SRC			=	$(addprefix $(SRC_DIR), $(SRC_FILES))

# BUILTINS
BI_DIR		=	src/builtins/
BI_FILES	=	env.c \
				export.c \
				unset.c
BUILTINS	=	$(addprefix $(BI_DIR), $(BI_FILES))

# ENV
ENV_DIR		=	src/env/
ENV_FILES	=	env_list.c
ENV			=	$(addprefix $(ENV_DIR), $(ENV_FILES))

# UTILS
UTILS_DIR	=	src/utils/
UTILS_FILES	=	utils_1.c
UTILS		=	$(addprefix $(UTILS_DIR), $(UTILS_FILES))

# OBJECTS
OBJ_DIR		=	objs/
OBJ_FILES	=	$(SRC:$(SRC_DIR)%.c=$(OBJ_DIR)%.o) \
				$(BUILTINS:$(BI_DIR).c=$(OBJ_DIR).o) \
				$(ENV:$(ENV_DIR).c=$(OBJ_DIR).o) \
				$(UTILS:$(UTILS_DIR).c=$(OBJ_DIR).o)

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

$(NAME): $(OBJ_FILES)
	@echo "\n$(BLUE)Compiling libft.$(CLEAR)"
	@make -sC libft
	@echo "$(GREEN)[libft --> OK]$(CLEAR)"
	@echo "$(BLUE)Compiling minishell program.$(CLEAR)"
	$(CC) $(FLAGS) $(LIBFT) -lreadline $(OBJ_FILES) -o $(NAME)
	@echo "$(GREEN)[minishell --> OK]\n$(CLEAR)$(GREEN)Success!$(CLEAR)"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(FLAGS) -c $< -o $@

clean:
	@echo "$(BLUE)Removing compiled files.$(CLEAR)"
	@make clean -sC libft
	$(RM) $(OBJ_DIR)
	@echo "$(GREEN)Object files removed correctly$(CLEAR)"

fclean: clean
	@echo "$(BLUE)Removing binary files.$(CLEAR)"
	@make fclean -sC libft
	$(RM) $(NAME)
	@echo "$(GREEN)Object files and binary removed correctly$(CLEAR)"

re: fclean all

.PHONY:	all clean fclean re
