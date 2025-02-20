NAME = minishell

SRCS = 	minishell.c 

EXEC = 	execution/pipex.c execution/utils_exec.c execution/utils_error.c \
		execution/utils_files.c execution/ft_here_doc.c execution/simple_exec.c execution/send_to_exec.c \
		execution/pipe_first.c execution/pipe_multi.c execution/utils_wildcard.c

PARSING = 	parsing/argv_parser.c parsing/token_parser.c parsing/utils_token.c parsing/ampersand_parse.c parsing/quote_parser.c \
			parsing/var_parser.c parsing/pip_free.c parsing/pip_init.c parsing/pip_parser.c parsing/pip_redir.c

BUILTINS = 	builtins/builtins_cd.c builtins/builtins_pwd.c builtins/builtins_exit.c builtins/builtins_echo.c \
			builtins/builtins_export.c builtins/builtins_unset.c  builtins/builtins_env.c 

UTILS = utils/utils_prompt.c utils/utils_print_error.c utils/utils_debug.c \
		utils/utils_list.c utils/utils_list2.c utils/utils_get.c \
		utils/utils_signal.c utils/utils_free.c

SRCS_BONUS = \

ALL_SRCS = $(SRCS) $(EXEC) $(PARSING) $(BUILTINS) $(UTILS)

OBJS = $(ALL_SRCS:.c=.o)

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
