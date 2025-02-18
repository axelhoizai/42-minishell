/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoizai <ahoizai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 13:17:11 by mdemare           #+#    #+#             */
/*   Updated: 2025/02/18 16:29:02 by ahoizai          ###   ########.fr       */
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

# define CMD_NOT_FOUND 127
# define PERMISSION_DENIED 126
# define EXIT_FAILURE 1
# define EXIT_SUCCESS 0
# define FILE_NOT_FOUND 2
# define INVALID_INPUT 3
# define PIPE_ERROR 4
# define FORK_ERROR 5
# define DUPLICATE_ERROR 6
# define EXEC_ERROR 7
# define MEMORY_ERROR 8

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

typedef struct s_data_term
{
	struct termios	original_term;
}	t_data_term;

typedef struct s_data
{
	int			exit_code;
	char		**my_envp;
	t_env_ms	*env_ms;
	char		**argv;
	bool		is_reading;
	t_data_term	*term;
}	t_data;

typedef struct s_command
{
	char	**args;
	int		arg_cnt;
	int		fd_in;
	int		fd_out;
	char	*input_file;
	char	*output_file;
	char	*limiter;
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
	int			*pid;
	int			start;
	int			pipe_cnt;
	int			cmd_count;
}	t_pipeline;

//-------------------------------UTILS-------------------------------

// utils_prompt
char		*get_prompt(t_env_ms *lst);

//utils_cd
void		change_dir(int argc, char **argv, t_pipeline *pip, t_data *data);

//utils_error
void		ft_print_error(char *builting, char *arg, char *msg);

// argv_parser
void		get_argv(char *input, t_data *data);

// quote_parser
char		**utils_parse_args(const char *str);

// utils_token
int			check_unclosed_quotes(const char *line);
void		init_parse(t_parse *parse, int size);
void		append_char(t_parse *parse, char c);
void		free_tokens(char **tokens);

// token_parser
char		*parse_token(char *line, int *i, t_data *data);
void		handle_variable(char *line, int *i, t_parse *parse, t_data *data);

// utils_ampersand
char		*replace_double_ampersand(char *arg);

// send_to_exec
bool		is_builtin(char *cmd);
void		handle_builtins(t_command *cmd, t_pipeline *pip, t_data *data);
void		send_to_exec(int argc, char **argv, t_data *data);

// utils_debug
void		print_tab(char **tab);
void		print_lst(t_env_ms *lst);

//utils_list
int			ms_lstsize(t_env_ms *lst);
void		ms_lstadd_back(t_env_ms **lst, t_env_ms *new);
void		ms_lstclear(t_env_ms **lst);
void		ms_lstdelone(t_env_ms **lst, char *env_key);
void		lst_to_tab(t_env_ms *lst, t_data *data);
t_env_ms	*ms_lstnew(char *env_key, char *env_value, bool equal_sign);
// t_env_ms	*sort_list(t_env_ms *lst);

//utils_get
t_data		*get_data(t_data *new_data);
int			get_process_id(void);
char		*get_uid(void);

//utils_pwd
void		get_dir(t_data *data, t_pipeline *pip);

//builtins_echo
void		ft_echo(int argc, char **argv);

// utils_free
void		free_var(void *var);
void		free_tab(char **tab);
void		free_term(t_data *data);

// utils signal
void		setup_signal_handlers(void);

// //-------------------------------BUILTINS----------------------------

//builtins_exit
void		handle_exit(t_pipeline *pip, t_data *data);

//builtins_export
bool		is_key(t_env_ms *lst, char *var);
t_env_ms	*ms_find(t_env_ms *lst, char *var);
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
void		free_execute(t_pipeline *pip, t_data *data);

//----------------------------BUILTINS-END---------------------------

//-------------------------------PIPEX-------------------------------

//here_doc
void		here_doc_init(t_pipeline *pip);
bool		is_hd(t_pipeline *pip);

//utils_exec
char		*get_path(char *cmd, char **envp);

//utils error
void		script_checker(char *cmd);

//utils_files
int			open_file(t_command *cmd, char *file, int mode);
int			open_outfile(t_command *cmd, char *file, t_data *data, int append);

//pipex
void		close_fds(t_pipeline *pip);
int			pipex(t_pipeline *pip, t_data *data);

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
void		print_pipeline(t_pipeline *pipeline);
void		init_pipe_start(t_pipeline *pip);

#endif
