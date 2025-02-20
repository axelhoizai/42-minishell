/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdemare <mdemare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 15:04:19 by mdemare           #+#    #+#             */
/*   Updated: 2025/02/20 09:33:14 by mdemare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	script_checker(char **cmd, char *cmd_path)
{
	char	**new_cmd;
	char 	*script_path;
	//voir leak
	printf("cmd = %s\n", cmd[0]);
	if ((ft_strstr(cmd[0], "./") && ft_strchr(cmd[0], ' '))
		|| access(cmd[0], X_OK) == -1)
	{
		ft_print_error(NULL, ft_strtok(cmd[0], " "), "No such file or directory");
		return ;
	}	
	if (ft_strstr(cmd[0], ".sh"))
	{
		script_path = ft_strdup(cmd[0]);
		new_cmd = (char **)ft_calloc(3, sizeof(char *));
		if (!new_cmd)
			return;
		new_cmd[0] = ft_strdup("/bin/bash");
		new_cmd[1] = script_path;
		new_cmd[2] = NULL;
		free_tab(cmd);
		cmd = new_cmd;
		cmd_path = cmd[0];
	}
	else if (ft_strstr(cmd[0], "./"))
		cmd_path = ft_strdup(cmd[0]);
}
