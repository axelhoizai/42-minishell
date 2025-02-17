/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoizai <ahoizai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 15:04:19 by mdemare           #+#    #+#             */
/*   Updated: 2025/02/17 13:31:42 by ahoizai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	script_checker(char *cmd)
{
	printf("cmd = %s\n", cmd);
	if ((ft_strstr(cmd, "./") && ft_strchr(cmd, ' '))
		|| access(cmd, X_OK) == -1)
		// print_error("no such file or directory: ", ft_strtok(cmd, " "), 1);
		ft_print_error(NULL, ft_strtok(cmd, " "), "No such file or directory");
}
