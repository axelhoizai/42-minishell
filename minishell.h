/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoizai <ahoizai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 13:17:11 by mdemare           #+#    #+#             */
/*   Updated: 2025/01/30 15:14:04 by ahoizai          ###   ########.fr       */
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


# define INPUT		1	//"<"
# define HEREDOC	2	//"<<"
# define TRUNC		3	//">"
# define APPEND		4	//">>"
# define PIPE		5	//"|"
# define CMD		6	//"|"
# define ARG		7	//"|"

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
	char 		**argv;
	// pid_t pid;
	// int pip[2];
}	t_data;

// typedef struct s_command
// {
// 	char	**args;
// 	char	*input_file;
// 	char	*output_file;
// 	int		append;
// 	int		heredoc;
// }	t_command;

// typedef struct s_pipeline
// {
// 	t_command	**commands;
// 	int			cmd_count;
// }	t_pipeline;

char		*get_promt(void);

//-------------------------------UTILS-------------------------------

//utils_cd
void		change_dir(int argc, char *dir, t_data *data);

//utils_error
void		ft_print_error(char *builting, char *arg, char *msg);

//utils_parsing
char		*join_argv(char **argv);

// utils_parse.c
void		skip_whitespace(const char *str, int *i);
int			check_unclosed_quotes(const char *line);
void		init_parse(t_parse *parse, int size);
void		append_char(t_parse *parse, char c);

// parsing_token.c
char		*parse_var(const char *token, int *index, t_data *data);
char		*parse_token(char *line, int *i, t_data *data);
char		**parse_args(char *line, t_data *data);
void		free_tokens(char **tokens);

char		*replace_double_ampersand(char *arg);

//utils
char		**get_argv(const char *input, t_data *data);
void		handle_sigint(int sig);
void		handle_pipe(char **argv, t_data *data);
void		handle_builtins(int argc, char **argv, t_data *data);

//utils_debug
void		print_tab(char **tab);
void		print_lst(t_env_ms *lst);

//utils_list
int			ms_lstsize(t_env_ms *lst);
void		ms_lstadd_back(t_env_ms **lst, t_env_ms *new);
t_env_ms	*ms_lstnew(char *env_key, char *env_value, bool equal_sign);
t_env_ms	*ms_lstlast(t_env_ms *lst);
t_env_ms	*sort_list(t_env_ms *lst);
void		ms_lstclear(t_env_ms **lst);
void		ms_lstdelone(t_env_ms **lst, char *env_key);
void		lst_to_tab(t_env_ms *lst, t_data *data);

//utils_data
void		ft_init(char **envp, int *is_start, t_data *data);

//utils_get
int			get_process_id(void);
char		*get_uid(void);

//utils_pwd
void		get_dir(t_data *data);

//utils_echo
char		*handle_n(char *flag);
char		*process_arg(char **builtin_tab, char **argv, int i);
char		**ft_echo_tab(int argc, char **argv);

//-------------------------------UTILS-END---------------------------

//-------------------------------BUILTINS----------------------------

//builtins_exit
void		handle_exit(char **argv, t_data	*data);

//builtins_echo
char		**ft_echo_tab(int argc, char **argv);
void		ft_echo(int argc, char **argv);

//builtins_export
bool		is_key(t_env_ms *lst, char *var);
t_env_ms	*ms_find(t_env_ms *lst, char *var);
void		print_export(t_env_ms *lst);
void		ft_export(char **argv, t_data *data);

//builtins_env
char		*get_envkey(char *env);
char		*get_envval(char *env);
void		init_env_ms(char **envp, t_data *data);
void		ft_env(t_data *data);

//builtins_unset
void		ft_unset(int argc, char *argv, t_data *data);

//builtin_exec
void		exec(char **argv, t_data *data);

//----------------------------BUILTINS-END---------------------------



//tester
void		sh_tester(char **av, t_data *data);













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

typedef struct s_command
{
	char	**args;
	char	*input_file;
	char	*output_file;
	int		append;
	int		heredoc;
}	t_command;

typedef struct s_pipeline
{
	t_command	**commands;
	int			cmd_count;
}	t_pipeline;

//here_doc
void	here_doc(t_pipeline *pip, int *p_fd, t_data *data);

//utils
char	*get_env_path(char **envp);
char	*get_path(char *cmd, char **envp);
char	*get_cmd(char *cmd);

//utils error
void	print_error(char *mgs, char *arg, int exit_code);
void	free_tab(char **tab);
int		args_checker(t_pipeline *pip);
void	script_checker(char *cmd);

//utils_files
int		open_file(char *file, int mode, int *p_fd);
void	open_outfile(t_pipeline *pip, int argc, int *fd_files, int *p_fd);
void	here_doc_checker(int *fd_files, t_pipeline *pip, t_data *data);

char	**utils_parse_args(const char *str);
int		pipex(t_pipeline *pip, t_data *data);


//parse_init
t_pipeline	*init_pipeline(void);
t_command	*init_command(void);

//parser_add
char		**add_to_tab(char **tab, const char *arg);
void		add_command_to_pipeline(t_pipeline *pipeline, t_command *cmd);

//parser_free
void		free_pipeline(t_pipeline *pipeline);

//parser
int			is_redirection(char *token);
void		handle_redirection(char **tokens, int *i, t_command *cmd);
t_command	*parse_command(char **tokens, int *i);
t_pipeline	*parse_pipeline(char **tokens);
void		print_pipeline(t_pipeline *pipeline);












#endif
