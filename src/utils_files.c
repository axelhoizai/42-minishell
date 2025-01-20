/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdemare <mdemare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 14:00:46 by mdemare           #+#    #+#             */
/*   Updated: 2025/01/20 17:41:12 by mdemare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	open_file(char *file, int mode, int *p_fd)
{
	int	fd;

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
		exit (1);
	}
	return (fd);
}

void	open_outfile(char **argv, int argc, int *fd_files, int *p_fd)
{
	if (ft_strcmp(argv[1], "here_doc") == 0)
		fd_files[1] = open_file(argv[argc - 1], 0, p_fd);
	else
		fd_files[1] = open_file(argv[argc - 1], 2, p_fd);
	if (fd_files[1] == -1)
	{
		close(p_fd[0]);
		close(p_fd[1]);
		if (fd_files[1] != -1)
			close (fd_files[1]);
		if (fd_files[0] != -1)
			close (fd_files[0]);
		exit(1);
	}
}

void	here_doc_checker(int *fd_files, char **argv)
{
	int	p_fd[2];

	if (ft_strcmp(argv[1], "here_doc") == 0)
	{
		if (pipe(p_fd) == -1)
			exit(PIPE_ERROR);
		if (fork() == 0)
		{
			close(p_fd[0]);
			here_doc(argv, p_fd);
			close(p_fd[1]);
			exit(0);
		}
		close(p_fd[1]);
		fd_files[0] = p_fd[0];
		wait(NULL);
	}
	else
		fd_files[0] = open_file(argv[1], 1, p_fd);
}
