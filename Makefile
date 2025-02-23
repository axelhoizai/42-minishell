NAME = minishell

SRCS = 	minishell.c 

LEXING = 	lexing/input_lexer.c lexing/lexer_parser.c lexing/lexer_expand.c \
			lexing/utils_lexer_expand.c lexing/lexer_expand_wildcard.c \
			lexing/utils_wildcard.c 

PARSING = 	parsing/token_parser.c parsing/pip_free.c parsing/pip_init.c \
			parsing/pip_parser.c parsing/pip_redir.c parsing/token_parser_utils.c

BUILTINS = 	builtins/builtins_cd.c builtins/builtins_pwd.c builtins/builtins_exit.c \
			builtins/builtins_echo.c builtins/builtins_export.c builtins/builtins_unset.c \
			builtins/builtins_env.c 

UTILS = 	utils/utils_prompt.c utils/utils_print_error.c utils/utils_debug.c \
			utils/utils_list.c utils/utils_list2.c utils/utils_get.c \
			utils/utils_signal.c utils/utils_free.c utils/utils_export.c utils/utils_hd.c

EXEC = 		execution/pipex.c execution/utils_exec.c execution/utils_error.c \
			execution/utils_files.c execution/ft_here_doc.c execution/simple_exec.c \
			execution/send_to_exec.c execution/pipe_first.c execution/pipe_multi.c \
			execution/utils_check.c

ALL_SRCS = $(SRCS) $(LEXING) $(PARSING) $(BUILTINS) $(UTILS) $(EXEC)

OBJS = $(ALL_SRCS:.c=.o)

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
	$(RM) $(OBJS)
	make clean -C ./libft

fclean: clean
	$(RM) $(NAME)
	make fclean -C ./libft

re: fclean all

.PHONY: all clean fclean re
