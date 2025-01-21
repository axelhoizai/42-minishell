/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_dir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdemare <mdemare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 09:56:34 by mdemare           #+#    #+#             */
/*   Updated: 2025/01/21 10:49:47 by mdemare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_dir(char *dir)
{
	if (dir && *dir)
		chdir(dir);
	get_argv("");
	get_promt();
	get_dir();
}

char	*get_dir(void)
{
	char	*currentpath;

	currentpath = getcwd(NULL, 0);
	return (currentpath);
}
