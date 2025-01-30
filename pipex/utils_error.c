/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdemare <mdemare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 15:04:19 by mdemare           #+#    #+#             */
/*   Updated: 2025/01/30 16:40:09 by mdemare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	print_error(char *mgs, char *arg, int exit_code)
{
	if (arg)
	{
		ft_putstr_fd(mgs, 2);
		ft_putendl_fd(arg, 2);
		exit(exit_code);
	}
	else
	{
		ft_putendl_fd(mgs, 2);
		exit(exit_code);
	}
}

int	args_checker(int argc, char **argv)
{
	if (argc < 5)
	{
		print_error("Usage: ./pipex filein \"cmd1\" \"cmd2\" fileout",
			NULL, INVALID_INPUT);
		return (-1);
	}
	else if (argc < 6 && ft_strstr(argv[1], "here_doc"))
	{
		print_error("Usage: ./pipex here_doc LIMITER \"cmd1\" \"cmd2\" fileout",
			NULL, INVALID_INPUT);
		return (-1);
	}
	else if (argc < 5 && !ft_strstr(argv[1], "here_doc"))
	{
		print_error("Usage: ./pipex filein \"cmd1\" \"cmd2\" fileout",
			NULL, INVALID_INPUT);
		return (-1);
	}
	if (ft_strstr(argv[3], "./"))
		script_checker(argv[3]);
	if (ft_strstr(argv[2], "./"))
		script_checker(argv[2]);
	return (1);
}

void	free_tab(char **tab)
{
	int i;

	if (!tab)
		return;
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	script_checker(char *cmd)
{
	printf("cmd = %s\n", cmd);
	if ((ft_strstr(cmd, "./") && ft_strchr(cmd, ' '))
		|| access(cmd, X_OK) == -1)
		print_error("no such file or directory: ", ft_strtok(cmd, " "), 1);
}
