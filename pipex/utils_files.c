/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoizai <ahoizai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 14:00:46 by mdemare           #+#    #+#             */
/*   Updated: 2025/02/08 18:30:46 by ahoizai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	open_file(t_data *data, char *file, int mode, int *p_fd)
{
	int	fd;
	(void)data;
	(void)p_fd;

	if (mode == 0)
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (mode == 1)
		fd = open(file, O_RDONLY);
	else
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	// if (fd == -1 && mode == 1)
	// {
	// 	perror(file);
	// 	// fd = open("/dev/null", O_RDONLY);
	// }
	// else if (access(file, R_OK) == -1 && mode == 1)
	// {
	// 	perror(file);
	// 	close(fd);
	// }
	// if ((fd == -1 || access(file, W_OK) == -1) && mode != 1)
	// {
	// 	perror(file);
	// 	// close(p_fd[0]);
	// }
	return (fd);
}

int	open_outfile(char *file, t_data *data, int here_doc)
{
	int	fd;
	
	if (here_doc == 1)
		fd = open_file(data, file, 0, NULL);
	else
		fd = open_file(data, file, 2, NULL);
	if (fd == -1)
		data->exit_code = 1;
	return (fd);
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
		// if (pip->cmds[0]->fd_in < 0)
		// {
		// 	fd_files[0] = -2;
		// 	return ;
		// }
		fd_files[0] = pip->cmds[0]->fd_in;
	}
}
