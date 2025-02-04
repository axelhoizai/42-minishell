/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoizai <ahoizai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 14:00:46 by mdemare           #+#    #+#             */
/*   Updated: 2025/02/04 12:58:38 by ahoizai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	open_file(t_data *data, char *file, int mode, int *p_fd)
{
	int	fd;
	(void)data;

	if (mode == 0)
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (mode == 1)
		fd = open(file, O_RDONLY);
	else
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1 && mode == 1)
	{
		perror(file);
		fd = open("/dev/null", O_RDONLY);
	}
	else if (access(file, R_OK) == -1 && mode == 1)
	{
		perror(file);
		close(fd);
	}
	if ((fd == -1 || access(file, W_OK) == -1) && mode != 1)
	{
		perror(file);
		close(p_fd[0]);
	}
	return (fd);
}

void	open_outfile(t_pipeline *pip, t_data *data, int argc, int *fd_files, int *p_fd)
{
	if (pip->cmds[0]->heredoc)
		fd_files[1] = open_file(data, pip->cmds[argc - 1]->output_file, 0, p_fd);
	else
		fd_files[1] = open_file(data, pip->cmds[argc - 1]->output_file, 2, p_fd);
	if (fd_files[1] == -1)
	{
		close(p_fd[0]);
		close(p_fd[1]);
		// if (fd_files[1] != -1)
		// 	close (fd_files[1]);
		if (fd_files[0] != -1)
			close (fd_files[0]);
		// free_tab(data->my_envp);
		// ms_lstclear(&data->env_ms);
		// free_pipeline(pip);
		data->exit_code = 1;
		handle_exit(pip, data);
		// exit(1);
	}
}

void	here_doc_checker(int *fd_files, t_pipeline *pip, t_data *data)
{
	int	p_fd[2];

	if (pip->cmds[0]->heredoc)
	{
		if (pipe(p_fd) == -1)
			exit(PIPE_ERROR);
		if (fork() == 0)
		{
			close(p_fd[0]);
			here_doc(pip, p_fd, data);
			close(p_fd[1]);
			ms_lstclear(&data->env_ms);
			free_tab(data->my_envp);
			free_pipeline(pip);
			exit(0);
		}
		close(p_fd[1]);
		fd_files[0] = p_fd[0];
		wait(NULL);
	}
	else
	{
		if (!pip->cmds[0]->input_file)
		{
			fd_files[0] = -1;
			return ;
		}
		fd_files[0] = open_file(data, pip->cmds[0]->input_file, 1, p_fd);
	}
}
