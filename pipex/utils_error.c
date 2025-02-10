/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalicem <kalicem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 15:04:19 by mdemare           #+#    #+#             */
/*   Updated: 2025/02/10 22:26:46 by kalicem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_error(char *mgs, char *arg, int exit_code)
{
	t_data *data;

	data = get_data(NULL);
	(void)exit_code;
	
	if (arg)
	{
		ft_putstr_fd(mgs, 2);
		ft_putendl_fd(arg, 2);
		data->exit_code = exit_code;
		// exit(exit_code);
	}
	else
	{
		ft_putendl_fd(mgs, 2);
		data->exit_code = exit_code;
		// exit(exit_code);
	}
}
//! reCheck all the input checking
int	args_checker(t_pipeline *pip)
{
	printf("%d\n", pip->cmd_count);
	if (pip->cmd_count < 2)
	{
		print_error("Usage: ./pipex filein \"cmd1\" \"cmd2\" fileout",
			NULL, INVALID_INPUT);
		return (-1);
	}
	else if (pip->cmd_count < 2 && pip->cmds[0]->heredoc)
	{
		print_error("Usage: ./pipex here_doc LIMITER \"cmd1\" \"cmd2\" fileout",
			NULL, INVALID_INPUT);
		return (-1);
	}
	else if (pip->cmd_count < 2 && !pip->cmds[0]->heredoc)
	{
		print_error("Usage: ./pipex filein \"cmd1\" \"cmd2\" fileout",
			NULL, INVALID_INPUT);
		return (-1);
	}
	// if (ft_strstr(argv[3], "./"))
	// 	script_checker(argv[3]);
	// if (ft_strstr(argv[2], "./"))
	// 	script_checker(argv[2]);
	return (1);
}

void	script_checker(char *cmd)
{
	printf("cmd = %s\n", cmd);
	if ((ft_strstr(cmd, "./") && ft_strchr(cmd, ' '))
		|| access(cmd, X_OK) == -1)
		print_error("no such file or directory: ", ft_strtok(cmd, " "), 1);
}
