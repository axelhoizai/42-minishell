NAME = minishell

SRCS = 	minishell.c src/pipex.c src/utils.c src/utils_error.c \
		src/utils_files.c src/ft_here_doc.c src/utils_parse.c \
		utils_prompt.c utils_dir.c 

SRCS_BONUS = \

OBJS = $(SRCS:.c=.o)
OBJS_BONUS = $(SRCS_BONUS:.c=.o)
LIBFT = ./libft/libft.a

CC = cc
CFLAGS += -Wall -Wextra -Werror -g -I./libft

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(OBJS) $(LIBFT) -o $(NAME) -lreadline

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	make -C ./libft

clean:
	$(RM) $(OBJS) $(OBJS_BONUS)
	make clean -C ./libft

fclean: clean
	$(RM) $(NAME)
	make fclean -C ./libft

re: fclean all

bonus: $(OBJS_BONUS) $(LIBFT)
	$(CC) $(OBJS_BONUS) $(LIBFT) -o $(NAME)

.PHONY: all clean fclean re
