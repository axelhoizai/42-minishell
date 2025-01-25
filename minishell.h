/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalicem <kalicem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 13:17:11 by mdemare           #+#    #+#             */
/*   Updated: 2025/01/24 23:36:35 by kalicem          ###   ########.fr       */
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

# include "pipex/pipex.h"

# define INPUT		1	//"<"
# define HEREDOC	2	//"<<"
# define TRUNC		3	//">"
# define APPEND		4	//">>"
# define PIPE		5	//"|"
# define CMD		6	//"|"
# define ARG		7	//"|"

typedef struct s_env_ms
{
	char			*env_var;
	struct s_env_ms	*next;
}			t_env_ms;

typedef struct s_data
{
	int			exit_code;
	char		**envp;
	t_env_ms	*env_ms;
	// pid_t pid;
	// int pip[2];
}			t_data;

char		*get_promt(void);
char		**get_argv(char *input, t_data *data);

//utils_cd
void		change_dir(int argc, char *dir);

//utils_pwd
void		get_dir(t_data *data);

//builtins_exit
void		handle_exit(char *input, char **argv);

//builtins_echo
char		**ft_echo_tab(int argc, char **argv);
void		ft_echo(int argc, char **argv, t_data *data);

//utils_echo
char		*handle_n(char *flag);
char		*parse_dollar(char *arg, t_data *data);
char		*process_arg(char **builtin_tab, char **argv, int i);
char		**ft_echo_tab(int argc, char **argv);

//builtins_export
void		print_export(t_env_ms *lst);
void		ft_export(t_env_ms *lst, char **argv);

//builtins_env
void		init_env_ms(t_data *data, char **envp);
void		ft_env(t_data *data);
//builtins_unset
void		ft_unset(int argc, char *argv);

//debug
void		print_tab(char **tab);

//utils_error
void		ft_print_error(char *builting, char *arg, char *msg, int exit_code);

//utils_parsing
char		*parse_quote(char *arg);

//utils_debug
void		print_tab(char **tab);
void		print_lst(t_env_ms *lst);

//utils_list
int			ms_lstsize(t_env_ms *lst);
void		ms_lstadd_back(t_env_ms **lst, t_env_ms *new);
t_env_ms	*ms_lstnew(char *env_var);
t_env_ms	*ms_lstlast(t_env_ms *lst);
t_env_ms	*sort_list(t_env_ms *lst);

//argv_parsing
char		**parse_args(const char *str);
char		*merge_args(char *current, const char *str, int start, int end);
int			handle_quotes(const char *str, int *index, char quote);
int			parse_quoted_arg(const char *str, int *i, char **current_arg);
int			parse_unquoted_arg(const char *str, int *i, char **current_arg);

#endif
