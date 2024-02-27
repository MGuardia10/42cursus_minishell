# NAME LIBFT
NAME			=	libft.a

# SOURCE FILES
SRC_DIR 		=	src/
SRC_FILES		=	ft_isalpha.c \
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
SRC				=	$(addprefix $(SRC_DIR), $(SRC_FILES))

# BONUS FILES
BONUS_DIR		=	src/bonus/
BONUS_FILES 	=	ft_lstnew_bonus.c \
					ft_lstadd_front_bonus.c \
					ft_lstsize_bonus.c \
					ft_lstlast_bonus.c \
					ft_lstadd_back_bonus.c \
					ft_lstdelone_bonus.c \
					ft_lstclear_bonus.c \
					ft_lstiter_bonus.c \
					ft_lstmap_bonus.c
BONUS			=	$(addprefix $(BONUS_DIR), $(BONUS_FILES))

# GNL_FILES
GNL_DIR			=	src/get_next_line/
GNL_FILES		=	get_next_line.c \
					get_next_line_utils.c
GNL				=	$(addprefix $(GNL_DIR), $(GNL_FILES))


# PRINTF_FILES
PRINTF_DIR		=	src/ft_printf/
PRINTF_FILES	=	ft_printf.c \
					ft_printf_utils.c
PRINTF			=	$(addprefix $(PRINTF_DIR), $(PRINTF_FILES))


# OBJECT FILES
OBJS_DIR		=	objs/
OBJS			=	$(SRC:$(SRC_DIR)%.c=$(OBJS_DIR)%.o)
OBJS_BONUS		=	$(BONUS:$(BONUS_DIR)%.c=$(OBJS_DIR)%.o)
OBJS_GNL		=	$(GNL:$(GNL_DIR)%.c=$(OBJS_DIR)%.o)
OBJS_PRINTF		=	$(PRINTF:$(PRINTF_DIR)%.c=$(OBJS_DIR)%.o)

# COMPILER OPTIONS
CC				=	gcc
FLAGS			=	-Wall -Werror -Wextra
RM				=	rm -f
INCLUDE 		=	-I inc

all:		$(NAME)

# ar: "archiver" -> agrupa varios archivos objeto en un archivo de libreria
# r: indica a "ar" que debe reemplazar o agregar archivos a la libreria
# c: indica que debe crear la libreria si no existe
$(NAME):	$(OBJS) bonus gnl printf
			ar -rcs $(NAME) $(OBJS)

bonus:		$(OBJS_BONUS)
			ar -rcs $(NAME) $(OBJS_BONUS)

gnl:		$(OBJS_GNL)
			ar -rcs $(NAME) $(OBJS_GNL)

printf:		$(OBJS_PRINTF)
			ar -rcs $(NAME) $(OBJS_PRINTF)

# -p: se utiliza para crear un directorio junto con sus directorios padres, en
# nuestro caso lo utilizamos para crear por primera vez el directorio objs/ y
# que no nos salte el error de que ya existe una vez ya se ha creado.
$(OBJS_DIR)%.o: $(SRC_DIR)%.c
		@mkdir -p $(OBJS_DIR) 
		${CC} ${FLAGS} $(INCLUDE) -c $< -o $@

$(OBJS_DIR)%.o: $(BONUS_DIR)%.c
		@mkdir -p $(OBJS_DIR)
		${CC} ${FLAGS} $(INCLUDE) -c $< -o $@

$(OBJS_DIR)%.o: $(GNL_DIR)%.c
		@mkdir -p $(OBJS_DIR)
		${CC} ${FLAGS} $(INCLUDE) -c $< -o $@

$(OBJS_DIR)%.o: $(PRINTF_DIR)%.c
		@mkdir -p $(OBJS_DIR)
		${CC} ${FLAGS} $(INCLUDE) -c $< -o $@

clean:
		$(RM) -r $(OBJS_DIR)

fclean:		clean
		$(RM) $(NAME)

re:		fclean all

.PHONY:	all bonus clean fclean re
