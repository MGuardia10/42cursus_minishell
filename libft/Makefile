################################################################################
# COMPILER OPTIONS
################################################################################

NAME			=	libft.a
CC				=	gcc
CFLAGS			=	-Wall -Werror -Wextra -g3
RM				=	rm -rf
INCLUDE 		=	-I inc

################################################################################
# SOURCE FILES
################################################################################

# VPATH
VPATH		=	src:src/bonus:src/ft_fprintf:src/ft_printf:src/get_next_line

# SRC
SRC		=	ft_isalpha.c \
			ft_isdigit.c \
			ft_isalnum.c \
			ft_isascii.c \
			ft_isprint.c \
			ft_strlen.c \
			ft_memset.c \
			ft_bzero.c \
			ft_memcpy.c \
			ft_memmove.c \
			ft_strlcpy.c \
			ft_strlcat.c \
			ft_toupper.c \
			ft_tolower.c \
			ft_strchr.c \
			ft_strrchr.c \
			ft_strncmp.c \
			ft_memchr.c \
			ft_memcmp.c \
			ft_strnstr.c \
			ft_atoi.c \
			ft_calloc.c \
			ft_strdup.c \
			ft_substr.c \
			ft_strjoin.c \
			ft_strtrim.c \
			ft_split.c \
			ft_itoa.c \
			ft_strmapi.c \
			ft_striteri.c \
			ft_putchar_fd.c \
			ft_putstr_fd.c \
			ft_putendl_fd.c \
			ft_putnbr_fd.c \
			ft_putchar.c \
			ft_putstr.c \
			ft_error.c \
			ft_custom_error.c \
			ft_free_matrix.c \
			ft_strcmp.c \
			ft_is_format.c \
			ft_is_readable.c \
			ft_atoi_base.c \
			ft_atol_base.c \
			ft_strtol.c \
			ft_change_pointers.c \
			ft_sort_ascii.c \
			ft_isspace.c \
			ft_arrsize.c

# BONUS
BONUS 	=	ft_lstnew_bonus.c \
			ft_lstadd_front_bonus.c \
			ft_lstsize_bonus.c \
			ft_lstlast_bonus.c \
			ft_lstadd_back_bonus.c \
			ft_lstdelone_bonus.c \
			ft_lstclear_bonus.c \
			ft_lstiter_bonus.c \
			ft_lstmap_bonus.c

# GNL
GNL		=	get_next_line.c \
			get_next_line_utils.c

# FPRINTF
FPRINTF	=	ft_fprintf.c \
			ft_fprintf_utils.c

# PRINTF
PRINTF	=	ft_printf.c \
			ft_printf_utils.c

# OBJECTS
OBJS_DIR		=	objs/
OBJ_FILES		=	$(SRC:%.c=$(OBJS_DIR)%.o) \
					$(BONUS:%.c=$(OBJS_DIR)%.o) \
					$(FPRINTF:%.c=$(OBJS_DIR)%.o) \
					$(PRINTF:%.c=$(OBJS_DIR)%.o) \
					$(GNL:%.c=$(OBJS_DIR)%.o)

################################################################################
# MAKEFILE RULES
################################################################################

all:		$(NAME)

# ar: "archiver" -> agrupa varios archivos objeto en un archivo de libreria
# r: indica a "ar" que debe reemplazar o agregar archivos a la libreria
# c: indica que debe crear la libreria si no existe
$(NAME):	$(OBJ_FILES)
			ar -rcs $(NAME) $(OBJ_FILES)

$(OBJS_DIR)%.o: %.c
		@mkdir -p $(OBJS_DIR)
		${CC} ${CFLAGS} -c $< $(INCLUDE) -o $@

clean:
		$(RM) $(OBJS_DIR)

fclean:		clean
		$(RM) $(NAME)

re:		fclean all

.PHONY:	all bonus clean fclean re
