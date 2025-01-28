NAME = minishell

SRCS = 	minishell.c \

PIPEX = pipex/pipex.c pipex/utils.c pipex/utils_error.c \
		pipex/utils_files.c pipex/ft_here_doc.c pipex/utils_parse.c 

PARSING = parsing/argv_parser.c parsing/token_parser.c parsing/utils_token.c 

PARSING_PIPE = pipe_parsing/parser_add.c pipe_parsing/parser_free.c pipe_parsing/parser_init.c pipe_parsing/parser.c

BUILTINS = 	builtins/builtins_cd.c builtins/builtins_pwd.c builtins/builtins_exit.c builtins/builtins_echo.c \
			builtins/builtins_export.c builtins/builtins_unset.c  builtins/builtins_env.c builtins/builtins_exec.c \
			builtins/builtins_exit_tester.c

UTILS = utils/utils_prompt.c utils/utils_print_error.c utils/utils_parsing.c utils/utils_debug.c utils/utils_echo.c \
		utils/utils_list.c utils/utils_list2.c utils/utils_data.c utils/utils_parsing_echo.c

SRCS_BONUS = \

ALL_SRCS = $(SRCS) $(PIPEX) $(PARSING_PIPE) $(PARSING) $(BUILTINS) $(UTILS)

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
