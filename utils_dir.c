/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_dir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoizai <ahoizai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 09:56:34 by mdemare           #+#    #+#             */
/*   Updated: 2025/01/21 14:17:29 by ahoizai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_dir(char *dir)
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
			chdir(dir);
		else if(!ft_strnstr(tmpdir, "//", ft_strlen(tmpdir)) && access(tmpdir, F_OK) == 0)
			chdir(tmpdir);
		else
			printf("no such file or directory: %s\n", dir);
		free(tmpdir);
	}
}

char	*get_dir(void)
{
	char	*currentpath;

	currentpath = getcwd(NULL, 0);
	return (currentpath);
}
