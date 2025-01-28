/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoizai <ahoizai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 13:17:11 by mdemare           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/01/28 15:39:52 by mdemare          ###   ########.fr       */
=======
/*   Updated: 2025/01/28 14:20:06 by ahoizai          ###   ########.fr       */
>>>>>>> 9383b40bc3e2ffd8311d505636ba5a615ab39e55
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

# include "pipex/pipex.h"

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
	// pid_t pid;
	// int pip[2];
}	t_data;

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
}	t_pipeline;

extern t_data	g_data;

char		*get_promt(void);
char		**get_argv(const char *input);

//utils_cd
void		change_dir(int argc, char *dir);

//utils_pwd
void		get_dir(void);

//builtins_exit
void		handle_exit(char **argv);

//builtins_echo
char		**ft_echo_tab(int argc, char **argv);
void		ft_echo(int argc, char **argv);

//utils_echo
char		*handle_n(char *flag);
char		*process_arg(char **builtin_tab, char **argv, int i);
char		**ft_echo_tab(int argc, char **argv);

//builtins_export
bool		is_key(t_env_ms *lst, char *var);
t_env_ms	*ms_find(t_env_ms *lst, char *var);
void		print_export(t_env_ms *lst);
void		ft_export(char **argv);

//builtins_env
char		*get_env_key(char *env);
char		*get_env_value(char *env);
void		init_env_ms(char **envp);
void		ft_env(void);

//builtins_unset
void		ft_unset(int argc, char *argv);

//builtin_exec
void		exec(char **argv, char *cmd, char **envp);

//utils_error
void		ft_print_error(char *builting, char *arg, char *msg, int exit_code);

// utils_parse.c
void	skip_whitespace(const char *str, int *i);
int		check_unclosed_quotes(const char *line);
void	init_parse(t_parse *parse, int size);
void	append_char(t_parse *parse, char c);

// token_utils.c
char	*parse_var(const char *token, int *index);
char	*parse_token(const char *line, int *i);
char	**parse_args(const char *line);
void	free_tokens(char **tokens);

char	*replace_double_ampersand(char *arg);

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
void		lst_to_tab(t_env_ms *lst);

//utils_data
void		ft_init(char **envp, int is_start);

//exit_tester
void		handle_exit_tester(char **argv);

////parsing_pipe
//parse_init
t_pipeline	*init_pipeline(void);
t_command	*init_command(void);

//parser_add
char		**add_to_tab(char **tab, const char *arg);
void		add_command_to_pipeline(t_pipeline *pipeline, t_command *cmd);

//parser_free
void	free_resources(t_pipeline *pipeline, char **tokens, char *line);

//parser
int			is_redirection(char *token);
void		handle_redirection(char **tokens, int *i, t_command *cmd);
t_command	*parse_command(char **tokens, int *i);
t_pipeline	*parse_pipeline(char **tokens);

#endif
