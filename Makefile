# NAME
NAME		=	minishell

# LIBFT
LIBFT		=	libft/libft.a

# VPATH
VPATH		=	src:src/builtins:src/env:src/executer:src/signals:src/utils

# SOURCE
# SRC_FILES	=	main.c
SRC			=	main2.c

# BUILTINS
BUILTINS	=	env.c \
				export.c \
				unset.c \
        		cd.c \
        		echo.c \
        		pwd.c \
				exit.c

# ENV
ENV			=	env_list.c \
				set_home.c \
				update_pwds.c \
				set_shlvl.c

# EXECUTER
EXECUTER	=	executer.c \
				handle_builtins.c \
				handle_simple_cmds.c \
				handle_compound_cmds.c \
				find_path.c \
				infiles.c \
				outfiles.c \
				heredoc.c \
				heredoc_utils.c

# SIGNALS
SIGNALS		=	signals.c

# UTILS
UTILS		=	utils_1.c \
				utils_2.c

# OBJECTS
OBJ_DIR		=	objs/
OBJ_FILES	=	$(SRC:%.c=$(OBJ_DIR)%.o) \
				$(BUILTINS:%.c=$(OBJ_DIR)%.o) \
				$(ENV:%.c=$(OBJ_DIR)%.o) \
				$(EXECUTER:%.c=$(OBJ_DIR)%.o) \
				$(SIGNALS:%.c=$(OBJ_DIR)%.o) \
				$(UTILS:%.c=$(OBJ_DIR)%.o)

# COMPILER
CC			=	gcc -g3
CFLAGS		=	-Wall -Wextra -Werror
LDFLAGS		=	-L/opt/homebrew/opt/readline/lib
CPPFLAGS	=	-I/opt/homebrew/opt/readline/include
# CPPFLAGS	=	-I/usr/local/Cellar/readline/8.2.10/include
# LDFLAGS     =	-L/usr/local/Cellar/readline/8.2.10/lib
RLFLAG		=	-lreadline
INCLUDES	=	-I libft/inc -I inc
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
	$(CC) $(CFLAGS) $(INCLUDES) $(CFLAGS) $(RLFLAG) $(CPPFLAGS) $(LDFLAGS) $(OBJ_FILES) $(LIBFT) -o $(NAME)
	@echo "$(GREEN)[minishell --> OK]\n$(CLEAR)$(GREEN)Success!$(CLEAR)"

$(OBJ_DIR)%.o: %.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) $(CPPFLAGS) -c $< -o $@

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
