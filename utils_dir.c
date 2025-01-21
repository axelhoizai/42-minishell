/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_dir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdemare <mdemare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 09:56:34 by mdemare           #+#    #+#             */
/*   Updated: 2025/01/21 18:51:10 by mdemare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_change_dir(char *cwd, char *tmpdir)
{
	if (cwd)
		free(cwd);
	if (tmpdir)
		free(tmpdir);
}

char	*parse_dir(char *dir)
{
	char	**tmp1;
	int		i;

	i = 0;
	tmp1 = utils_parse_args(dir);
	if(access(*tmp1, F_OK) == 0)
	{
		dir = ft_strdup(*tmp1);
		free_tab(tmp1);
		return (dir);
	}
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
		dir = parse_dir(dir);
	cwd = getcwd(NULL, 0);
	tmpdir = ft_strjoin(cwd, dir);
	if (argc > 2)
		printf("minishell: cd: too many arguments\n");//echo $? = 1
	else if (!dir)
		chdir(getenv("HOME"));
	else if(open(dir, O_RDONLY | __O_DIRECTORY) == -1)
		printf("minishell: cd: %s: Not a directory\n", dir);//echo $? = 1
	else if(access(dir, F_OK) == 0)
		chdir(dir);
	else if(!ft_strnstr(tmpdir, "//", ft_strlen(tmpdir)) && access(tmpdir, F_OK) == 0)
		chdir(tmpdir);
	else
		printf("minishell: cd: %s: No such file or directory\n", dir);
		// perror("minishell: cd");
	free_change_dir(cwd, tmpdir);
	// free(dir);
}

char	*get_dir(void)
{
	char	*currentpath;

	currentpath = getcwd(NULL, 0);
	return (currentpath);
}
