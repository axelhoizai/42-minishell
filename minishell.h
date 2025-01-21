/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdemare <mdemare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 13:17:11 by mdemare           #+#    #+#             */
/*   Updated: 2025/01/21 18:27:06 by mdemare          ###   ########.fr       */
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
# include "src/pipex.h"
# include <sys/types.h>
# include <dirent.h>
# include <errno.h>

char	*get_promt(void);
char	**get_argv(char *input);

//utils_dir
void	change_dir(int argc, char *dir);
char	*get_dir(void);

void	handle_exit(char *input, char **argv);

void	ft_echo(char **input);

#endif
