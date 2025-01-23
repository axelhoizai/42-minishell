/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdemare <mdemare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 13:17:11 by mdemare           #+#    #+#             */
/*   Updated: 2025/01/23 11:36:09 by mdemare          ###   ########.fr       */
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

typedef struct s_data
{
	int exit_code;
	// pid_t pid;
	// int pip[2];
} t_data;

char	*get_promt(void);
char	**get_argv(char *input, t_data *data);

//utils_cd
void	change_dir(int argc, char *dir);

//utils_pwd
char	*get_dir(void);

//builtins_exit
void	handle_exit(char *input, char **argv);

//builtins_echo
char	**ft_echo_tab(int argc, char **argv);
void	ft_echo(int argc, char **argv, t_data *data);


//builtins_export
void	ft_export(int argc, char *argv);

//builtins_env
void	ft_env(int argc, char *argv);

//builtins_unset
void	ft_unset(int argc, char *argv);

//debug
void	print_tab(char **tab);

//utils_error
void	ft_print_error(char *builting, char *arg, char *msg, int exit_code);

//utils_parsing
char	*parse_quote(char *arg);

//utils_debug
void	print_tab(char **tab);

#endif
