/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdemare <mdemare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 15:04:19 by mdemare           #+#    #+#             */
/*   Updated: 2025/02/21 18:14:14 by mdemare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	set_sheban(char ***cmd)
{
	char	*script_path;

	script_path = ft_strdup(*cmd[0]);
	free(*cmd[0]);
	*cmd[0] = script_path;
	*cmd[1] = NULL;
}

void	script_checker(char ***cmd)
{
	if (ft_strstr(*cmd[0], "./") && access(*cmd[0], X_OK) == -1)
	{
		ft_print_error(NULL, ft_strtok(*cmd[0], " "),
			"No such file or directory");
		if (access(*cmd[0], F_OK) == 0)
			*cmd[0] = NULL;
	}
	else if (ft_strstartwith(*cmd[0], "./")
		&& ft_strendwith(*cmd[0], ".sh") && access(*cmd[0], F_OK) == 0)
		set_sheban(cmd);
}
