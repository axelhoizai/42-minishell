/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdemare <mdemare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 14:00:46 by mdemare           #+#    #+#             */
/*   Updated: 2025/02/14 19:10:59 by mdemare          ###   ########.fr       */
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
