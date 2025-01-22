/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoizai <ahoizai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 13:17:11 by mdemare           #+#    #+#             */
/*   Updated: 2025/01/22 19:44:03 by ahoizai          ###   ########.fr       */
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

char	*get_promt(void);
char	**get_argv(char *input);

//utils_cd
void	change_dir(int argc, char *dir);

//utils_pwd
char	*get_dir(void);

//builtins_exit
void	handle_exit(char *input, char **argv);

//builtins_echo
char	**ft_echo_tab(int argc, char **argv);
void	ft_echo(int argc, char **argv);


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

#endif
