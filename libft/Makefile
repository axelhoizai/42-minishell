NAME = libft.a
CC = cc

CFLAGS += -c -g -Wall -Wextra -Werror -I$(INCLUDES_DIR)

SRCS_DIR = src/

SRCS_IS_DIR = ft_is/
SRCS_IS = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_isspace.c  ft_isnumeric.c \

SRCS_STR_DIR = ft_str/
SRCS_STR = ft_strchr.c ft_strdup.c ft_striteri.c ft_strjoin.c \
		   ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strmapi.c \
		   ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_strtrim.c \
		   ft_strtok.c ft_substr.c ft_split.c ft_strcat.c \
		   ft_strcpy.c ft_strstr.c ft_strcmp.c ft_str_tolower.c \
		   ft_str_toupper.c ft_strdup_tab.c ft_str_startwith.c \
		   ft_str_endwith.c ft_str_countchar.c ft_dup_tab_index.c

SRCS_TO_DIR = ft_to/
SRCS_TO = ft_atol.c ft_atoi.c ft_itoa.c ft_tolower.c ft_toupper.c \
		  ft_hex_to_uint.c ft_int_to_rgb.c \

SRCS_MEM_DIR = ft_mem/
SRCS_MEM = ft_bzero.c ft_calloc.c ft_memchr.c ft_memcmp.c \
		   ft_memcpy.c ft_memmove.c ft_memset.c ft_realloc.c ft_safe_malloc.c \

SRCS_PUT_DIR = ft_put/
SRCS_PUT =	ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \

SRCS_LST_DIR = ft_lst/
SRCS_LST = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
		   ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c \

SRCS_FT_PRINTF_DIR = ft_printf/
SRCS_FT_PRINTF = ft_print_char.c ft_print_hex.c ft_print_nbr.c ft_print_str.c \
				 ft_print_unsigned.c ft_printf.c ft_print_ptr.c \

SRCS_GET_NEXT_LINE_DIR = get_next_line/
SRCS_GET_NEXT_LINE = get_next_line.c get_next_line_utils.c \

SRCS_FILES = $(addprefix $(SRCS_IS_DIR), $(SRCS_IS))
SRCS_FILES += $(addprefix $(SRCS_STR_DIR), $(SRCS_STR))
SRCS_FILES += $(addprefix $(SRCS_TO_DIR), $(SRCS_TO))
SRCS_FILES += $(addprefix $(SRCS_MEM_DIR), $(SRCS_MEM))
SRCS_FILES += $(addprefix $(SRCS_PUT_DIR), $(SRCS_PUT))
SRCS_FILES += $(addprefix $(SRCS_LST_DIR), $(SRCS_LST))
SRCS_FILES += $(addprefix $(SRCS_FT_PRINTF_DIR), $(SRCS_FT_PRINTF))
SRCS_FILES += $(addprefix $(SRCS_GET_NEXT_LINE_DIR), $(SRCS_GET_NEXT_LINE))

SRCS += $(addprefix $(SRCS_DIR), $(SRCS_FILES)) 
OBJS = $(SRCS:.c=.o)

$(NAME): $(OBJS)
	ar crs $(NAME) $(OBJS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

all: $(NAME)

.PHONY = clean fclean re all 
