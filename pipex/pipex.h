/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoizai <ahoizai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 10:56:43 by mdemare           #+#    #+#             */
/*   Updated: 2025/01/29 19:23:27 by ahoizai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

// # include "../libft/libft.h"
// # include <stdio.h>
// # include <unistd.h>
// # include <fcntl.h>
// # include <sys/wait.h>
// # include "../minishell.h"

// # define CMD_NOT_FOUND 127
// # define PERMISSION_DENIED 126
// # define EXIT_FAILURE 1
// # define EXIT_SUCCESS 0
// # define FILE_NOT_FOUND 2
// # define INVALID_INPUT 3
// # define PIPE_ERROR 4
// # define FORK_ERROR 5
// # define DUPLICATE_ERROR 6
// # define EXEC_ERROR 7
// # define MEMORY_ERROR 8

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

// //here_doc
// void	here_doc(t_pipeline *pip, int *p_fd, t_data *data);

// //utils
// char	*get_env_path(char **envp);
// char	*get_path(char *cmd, char **envp);
// char	*get_cmd(char *cmd);

// //utils error
// void	print_error(char *mgs, char *arg, int exit_code);
// void	free_tab(char **tab);
// int		args_checker(t_pipeline *pip);
// void	script_checker(char *cmd);

// //utils_files
// int		open_file(char *file, int mode, int *p_fd);
// void	open_outfile(t_pipeline *pip, int argc, int *fd_files, int *p_fd);
// void	here_doc_checker(int *fd_files, t_pipeline *pip, t_data *data);

// char	**utils_parse_args(const char *str);
// int		pipex(t_pipeline *pip, t_data *data);


// //parse_init
// t_pipeline	*init_pipeline(void);
// t_command	*init_command(void);

// //parser_add
// char		**add_to_tab(char **tab, const char *arg);
// void		add_command_to_pipeline(t_pipeline *pipeline, t_command *cmd);

// //parser_free
// void		free_pipeline(t_pipeline *pipeline);

// //parser
// int			is_redirection(char *token);
// void		handle_redirection(char **tokens, int *i, t_command *cmd);
// t_command	*parse_command(char **tokens, int *i);
// t_pipeline	*parse_pipeline(char **tokens);
// void		print_pipeline(t_pipeline *pipeline);

#endif
