/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoizai <ahoizai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 13:17:11 by mdemare           #+#    #+#             */
/*   Updated: 2025/02/27 14:05:24 by ahoizai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <unistd.h>
# include <sys/types.h>
# include <dirent.h>
# include <stdbool.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <termios.h>
# include <sys/ioctl.h>

# define PIPE_ERROR 4
# define FORK_ERROR 5

# define MAX_FILES 1024
# define MSG_ERROR_FILE "No such file or directory"
# define MSG_IS_DIR "Is a directory"
# define MSG_ERROR_SYNTAX "syntax error near unexpected token"

typedef struct s_parse
{
	char	*buffer;
	int		len;
	int		capacity;
	int		in_single;
	int		in_double;
}	t_parse;

typedef struct s_env_ms
{
	char			*key;
	char			*value;
	bool			equal_sign;
	struct s_env_ms	*next;
}	t_env_ms;

typedef struct s_data
{
	int			exit_code;
	char		**my_envp;
	t_env_ms	*env_ms;
	bool		is_reading;
	char		*oldpwd;
	char		*pwd;
}	t_data;

typedef struct s_command
{
	char	**args;
	int		arg_cnt;
	int		fd_in;
	int		fd_out;
	char	*input_file;
	char	*output_file;
	char	**limiters;
	int		trunc;
	int		append;
	int		heredoc;
	int		in_error;
	int		out_error;
}	t_command;

typedef struct s_pipeline
{
	t_command	**cmds;
	pid_t		*pid;
	int			start;
	int			pipe_cnt;
	int			cmd_count; // garder??
}	t_pipeline;

//-------------------------------UTILS-------------------------------

// input_lexer
void		input_lexer(char *input, t_data *data);

// lexer_parser
char		*parse_lexer(char *line, int *i, t_data *data);
void		update_quote_state(const char *line, int *in_s, int *in_d, int i);

// utils_wildcard
void		check_and_expand_wildcard(char **input);

// utils_lexer
int			check_unclosed_quotes(const char *line);
void		init_parse(t_parse *parse, int size);
void		append_char(t_parse *parse, char c);
bool		handle_check_var(char *line, int *i, t_data *data, t_parse *parse);
void		handle_variable(char *line, int *i, t_parse *parse, t_data *data);

//utils wildcard
void		expand_wildcard(char **str);
char		*extract_word(char *input, int *i, int *in_single, int *in_double);

//check_and_expand_operators
void		check_and_expand_operators(char **input);

//format_operators_and_redirections
void		format_operators_and_redirections(char **input);

//check_syntax_error
int			check_syntax_errors(char *input);
int			is_syntax_error(char *input, int i, int expect_word, int prev_op);

// token_parser_utils
int			is_double_operator(const char *input, int i);
int			is_operator(char c);

// utils_prompt
char		*get_prompt(t_env_ms *lst);

//utils_cd
void		change_dir(int argc, char **argv, t_data *data);

//utils_error
void		ft_print_error(char *builting, char *arg, char *msg);

// send_to_exec
void		handle_builtins(t_command *cmd, t_pipeline *pip, t_data *data);
void		send_to_exec(char **argv, t_data *data);

// utils_check
bool		check_redir_pipe(char **tokens);
bool		is_pipe(char **argv);
bool		is_token_pipe(char *token);
bool		is_builtin(t_command *cmd);

// utils_debug
void		print_lst(t_env_ms *lst);

//utils_list
int			ms_lstsize(t_env_ms *lst);
void		ms_lstadd_back(t_env_ms **lst, t_env_ms *new);
void		ms_lstclear(t_env_ms **lst);
void		ms_lstdelone(t_env_ms **lst, char *env_key);
void		lst_to_tab(t_env_ms *lst, t_data *data);
t_env_ms	*ms_lstnew(char *env_key, char *env_value, bool equal_sign);

//utils_get
t_data		*get_data(t_data *new_data);
int			get_process_id(void);
char		*get_uid(void);

//utils_pwd
void		get_dir(t_data *data);
void		update_pwd(void);
void		update_oldpwd(void);

//builtins_echo
void		ft_echo(int argc, char **argv);

// utils_free
void		free_var(void *var);
void		free_tab(char **tab);

// utils signal
void		setup_signal_handlers(void);

// //-------------------------------BUILTINS----------------------------

//builtins_exit
void		handle_exit(t_command *cmd, t_pipeline *pip, t_data *data);

//builtins_export & utils_export
bool		is_key(t_env_ms *lst, char *var);
t_env_ms	*ms_find(t_env_ms *lst, char *var);
int			find_index(char *str);
void		ft_export(char **argv, t_data *data);

//builtins_env
char		*get_envkey(char *env);
char		*get_envval(char *env);
void		init_env_ms(char **envp, t_data *data);
void		ft_env(t_data *data);

//builtins_unset
void		ft_unset(char **argv, t_data *data);

//builtin_exec
void		simple_exec(t_pipeline *pip, t_data *data);
void		execute(char **cmd, t_pipeline *pip, t_data *data);
void		free_execute(t_pipeline *pip, t_data *data, char *cmd_path);

//----------------------------BUILTINS-END---------------------------

//-------------------------------PIPEX-------------------------------

//here_doc
void		here_doc_init(t_pipeline *pip);
bool		is_hd(t_pipeline *pip);
int			limiter_count(t_pipeline *pip);

//utils_exec
char		*get_path(char *cmd, char **envp);

//utils error
void		script_checker(char ***cmd);

//utils_files
int			open_file(t_command *cmd, char *file, int mode);
int			open_outfile(t_command *cmd, char *file, t_data *data, int append);
void		files_checker(char	*file, t_data *data);

//pipex
void		close_fds(t_pipeline *pip);
int			pipex(t_pipeline *pip, t_data *data);
void		executing(t_command *cmd, t_pipeline *pip, t_data *data);
void		first_pipe(t_command *cmd, t_pipeline *pip,
				int *p_fd, t_data *data);

void		multi_pipe(t_pipeline *pip, int *p_fd, t_data *data, int *i);

//pip_init
t_pipeline	*init_pipeline(void);
t_command	*init_command(void);
int			*init_pid(t_pipeline *pip);
char		**add_to_tab(char **tab, const char *arg);
void		add_command_to_pipeline(t_pipeline *pipeline, t_command *cmd);

//pip_free
void		free_pipeline(t_pipeline *pipeline);

//pip_redir
void		handle_redirec(char **tokens, int *i, t_command *cmd, t_data *data);

//pip_parser
t_pipeline	*parse_pipeline(char **tokens, t_data *data);
void		init_pipe_start(t_pipeline *pip);
char		*rm_quotes(const char *str);

#endif
