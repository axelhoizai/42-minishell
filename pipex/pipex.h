/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdemare <mdemare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 10:56:43 by mdemare           #+#    #+#             */
/*   Updated: 2025/01/23 19:49:26 by mdemare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>

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

typedef struct s_arg
{
	int		argc;
	char	**argv;
}			t_arg;

//here_doc
void	here_doc(char **argv, int *p_fd);

//utils
char	*get_env_path(char **envp);
char	*get_path(char *cmd, char **envp);
char	*get_cmd(char *cmd);

//utils error
void	print_error(char *mgs, char *arg, int exit_code);
void	free_tab(char **tab);
int		args_checker(int argc, char **argv);
void	script_checker(char *cmd);

//utils_files
int		open_file(char *file, int mode, int *p_fd);
void	open_outfile(char **argv, int argc, int *fd_files, int *p_fd);
void	here_doc_checker(int *fd_files, char **argv);

char	**utils_parse_args(const char *str);

#endif
