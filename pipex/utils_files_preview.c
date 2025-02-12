/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_files_preview.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalicem <kalicem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 14:00:46 by mdemare           #+#    #+#             */
/*   Updated: 2025/02/12 01:02:57 by kalicem          ###   ########.fr       */
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

void	here_doc_checker(int *fd_files, t_pipeline *pip, t_data *data, int *i)
{
	int		p_fd[2];
	int		last_fd;
	pid_t	child;

	(void)data;
	last_fd = -1;
	if (!pip || !pip->cmds[*i] || !pip->cmds[*i]->limiters)
		return;
	if (pip->cmds[*i]->heredoc && pip->cmds[*i]->limiters)
	{
		if (pipe(p_fd) == -1)
			exit(PIPE_ERROR);
		child = fork();
		if (child == -1)
			exit(FORK_ERROR);
		if (child == 0)
		{
			close(p_fd[0]);
			here_doc(pip->cmds[*i]->limiters, p_fd);
			exit(0);
		}
		close(p_fd[1]);
		if (last_fd > 0)
			close(last_fd);
		last_fd = p_fd[0];
		waitpid(child, NULL, 0);
	}
	close(fd_files[0]);
}