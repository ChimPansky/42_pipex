NAME = libft.a
CC = cc
CFLAGS = -Wall -Werror -Wextra -g
INCLUDE_DIR = ../include/
HEADER = $(INCLUDE_DIR)libft.h

#Colors
DEF_COLOR = \033[0;39m
GRAY = \033[0;90m
RED = \033[0;91m
GREEN = \033[0;92m
YELLOW = \033[0;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m

SRC_FILES = ft_atoi ft_bzero ft_calloc ft_isalnum ft_isalpha ft_isascii \
	ft_isdigit ft_isprint ft_isspace ft_itoa ft_memchr ft_memcmp \
	ft_memcpy ft_memmove ft_memrchr ft_memset ft_putchar_fd \
	ft_putendl_fd ft_putnbr_fd ft_putstr_fd ft_split ft_strchr \
	ft_strdup ft_striteri ft_strjoin ft_strlcat ft_strlcpy ft_strlen \
	ft_strmapi ft_strncmp ft_strnstr ft_strrchr ft_strtrim ft_substr \
	ft_tolower ft_toupper	\
	ft_lstnew_bonus ft_lstadd_front_bonus ft_lstsize_bonus \
	ft_lstlast_bonus ft_lstadd_back_bonus ft_lstdelone_bonus \
	ft_lstclear_bonus ft_lstiter_bonus ft_lstmap_bonus	\
	ft_free_and_null \
	ft_file_get_extension ft_file_check_extension \
	ft_file_exists \
	ft_free_splitted \
	ft_get_int_order_base ft_itoa_base_signed ft_itoa_base_unsigned	\
	ft_iif \
	ft_strjoin_free ft_substr_free \
	ft_strreplicate \
	ft_strlpad ft_strrpad ft_strlpad_free ft_strrpad_free \
	ft_str_isnum ft_str_isint ft_str_chr_replace \
	ft_abs ft_max \
	ft_print_memory	\
	ft_printf ft_printf_config ft_printf_manipulations \
	ft_printf_output ft_printf_utils \
	get_next_line


SRC = $(addsuffix .c, $(SRC_FILES))

OBJ = $(SRC:.c=.o)

$(NAME): $(OBJ) $(HEADER)
	ar -rs $(NAME) $(OBJ)
	@echo "$(GREEN)Library $(NAME) created!$(DEF_COLOR)"

%.o : %.c $(HEADER)
#$(CC) $(CFLAGS) -c $< -o $@
	$(CC) -I $(INCLUDE_DIR) $(CFLAGS) -c $< -o $@

all: $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
