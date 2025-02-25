/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoizai <ahoizai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 14:00:46 by mdemare           #+#    #+#             */
/*   Updated: 2025/02/25 12:47:57 by ahoizai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	chck_perm_in(t_command *cmd, char *file)
{
	if (access(file, R_OK | F_OK) != 0 && access(file, F_OK) == 0 
		&& cmd->in_error == 0 && cmd->out_error == 0)
		{
			ft_print_error(NULL, file, "Permission denied");
			cmd->in_error = 1;
		}
}

int	open_file(t_command *cmd, char *file, int mode)
{
	int	fd;

	if (mode == 1)
	{
		chck_perm_in(cmd, file);
		fd = open(file, O_RDONLY);
	}
	else
	{
		if (access(file, R_OK | W_OK) != 0 && access(file, F_OK) == 0
			&& cmd->in_error == 0 && cmd->out_error == 0)
		{
			ft_print_error(NULL, file, "Permission denied");
			cmd->out_error = 1;
		}
		if (mode == 0)
			fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
	return (fd);
}

int	open_outfile(t_command *cmd, char *file, t_data *data, int append)
{
	int	fd;

	if (append == 1)
		fd = open_file(cmd, file, 0);
	else
		fd = open_file(cmd, file, 2);
	if (fd == -1)
		data->exit_code = 1;
	return (fd);
}

void	files_checker(char	*file, t_data *data)
{
	// printf("exit_code = %d\n", data->exit_code);
	// if (data->exit_code == 0)
	// {
		if (access(file, R_OK != 0) && access(file, F_OK) == 0)
		{
			ft_print_error(NULL, file, "Permission denied");
			data->exit_code = 126;
		}
		else if (access(file, F_OK) == 0)
		{
			ft_print_error(NULL, file, MSG_IS_DIR);
			data->exit_code = 126;
		}
		else if (access(file, F_OK) == -1)
		{
			ft_print_error(NULL, ft_strtok(file, " "), MSG_ERROR_FILE);
			data->exit_code = 127;
		}
	// }
}
