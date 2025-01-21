/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_dir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdemare <mdemare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 09:56:34 by mdemare           #+#    #+#             */
/*   Updated: 2025/01/21 13:54:50 by mdemare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	change_dir(char *dir)
{
	char	*tmpdir;
	char	*cwd;
	
	tmpdir = NULL;
	if (dir && *dir)
	{
		cwd = getcwd(NULL, 0);
		tmpdir = ft_strjoin(cwd, dir);
		free(cwd);
		if(access(dir, F_OK) == 0)
		{
			chdir(dir);
			free(tmpdir);
			return (1);
		}
		else if(!ft_strnstr(tmpdir, "//", ft_strlen(tmpdir)) && access(tmpdir, F_OK) == 0)
		{
			chdir(tmpdir);
			free(tmpdir);
			return (1);
		}
		else
			printf("no such file or directory: %s\n", dir);
		free(tmpdir);
	}
	return (-1);
}

char	*get_dir(void)
{
	char	*currentpath;

	currentpath = getcwd(NULL, 0);
	return (currentpath);
}
