/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoizai <ahoizai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 15:04:19 by mdemare           #+#    #+#             */
/*   Updated: 2025/02/21 11:21:48 by ahoizai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**set_sheban(char **cmd)
{
	char	**new_cmd;
	char	*script_path;

	script_path = ft_strdup(cmd[0]);
	new_cmd = (char **)ft_calloc(3, sizeof(char *));
	if (!new_cmd)
		return (NULL);
	new_cmd[0] = ft_strdup("/bin/bash");
	new_cmd[1] = script_path;
	new_cmd[2] = NULL;
	return (new_cmd);
}

char	**script_checker(char **cmd)
{
	if (ft_strstr(cmd[0], "./") && access(cmd[0], X_OK) == -1)
	{
		ft_print_error(NULL, ft_strtok(cmd[0], " "),
			"No such file or directory");
		return (NULL);
	}
	else if (ft_strstr(cmd[0], ".sh"))
		return (set_sheban(cmd));
	else if (ft_strstr(cmd[0], "./"))
		return (cmd);
	return (NULL);
}
