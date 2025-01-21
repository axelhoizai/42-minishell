/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_dir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdemare <mdemare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 09:56:34 by mdemare           #+#    #+#             */
/*   Updated: 2025/01/21 16:57:36 by mdemare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_change_dir(char *dir, char *cwd, char *tmpdir)
{
	free(cwd);
	free(dir);
	free(tmpdir);
}

char	*parse_dir(char *dir)
{
	char	**tmp1;
	int		i;

	i = 0;

	tmp1 = utils_parse_args(dir);
	while (tmp1[i])
		i++;
	if (i > 1)
		dir = ft_strjoin(tmp1[0], tmp1[1]);
	free_tab(tmp1);
	return (dir);
}

void	change_dir(int argc, char *dir)
{
	char	*tmpdir;
	char	*cwd;

	tmpdir = NULL;
	if (dir)
		parse_dir(dir);
	cwd = getcwd(NULL, 0);
	tmpdir = ft_strjoin(cwd, dir);
	if (argc > 2)
		printf("minishell: cd: too many arguments\n");
	else if (!dir)
		chdir(getenv("HOME"));
	else if(access(dir, F_OK) == 0)
		chdir(dir);
	else if(!ft_strnstr(tmpdir, "//", ft_strlen(tmpdir)) && access(tmpdir, F_OK) == 0)
		chdir(tmpdir);
	else
		printf("minishell: cd: %s: No such file or directory\n", dir);
	free_change_dir(dir, cwd, tmpdir);
}

char	*get_dir(void)
{
	char	*currentpath;

	currentpath = getcwd(NULL, 0);
	return (currentpath);
}
