/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoizai <ahoizai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 14:00:46 by mdemare           #+#    #+#             */
/*   Updated: 2025/02/17 12:58:07 by ahoizai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	open_file(char *file, int mode)
{
	int	fd;

	if (mode == 1)
	{
		if (access(file, R_OK | F_OK) != 0)
		{
			ft_print_error(NULL, file, "Permission denied");
			fd = -1;
		}
		else
			fd = open(file, O_RDONLY);
	}
	else
	{
		if (access(file, R_OK | W_OK) != 0)
		{
			ft_print_error(NULL, file, "Permission denied");
			fd = -1;
		}
		else if (mode == 0)
			fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
	return (fd);
}

int	open_outfile(char *file, t_data *data, int here_doc)
{
	int	fd;

	if (here_doc == 1)
		fd = open_file(file, 0);
	else
		fd = open_file(file, 2);
	if (fd == -1)
		data->exit_code = 1;
	return (fd);
}
