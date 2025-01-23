/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoizai <ahoizai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 09:56:34 by mdemare           #+#    #+#             */
/*   Updated: 2025/01/23 11:20:51 by ahoizai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_change_dir(char *cwd, char *tmpdir)
{
	if (cwd)
		free(cwd);
	if (tmpdir)
		free(tmpdir);
}

// char	*parse_dir(char *dir)
// {
// 	char	**tmp1;
// 	int		i;

// 	i = 0;
// 	tmp1 = parse_quote(dir);
// 	if(access(*tmp1, F_OK) == 0)
// 	{
// 		dir = ft_strdup(*tmp1);
// 		free_tab(tmp1);
// 		return (dir);
// 	}
// 	while (tmp1[i])
// 		i++;
// 	if (i > 1)
// 		dir = ft_strjoin(tmp1[0], tmp1[1]);
// 	free_tab(tmp1);
// 	return (dir);
// }


char	*parse_dir(char *dir) //cd "ho""la"
{
	char *tmp1;

	tmp1 = parse_quote(dir); //a free
	if (tmp1 == NULL)
		return (dir);
	else
		return (tmp1);
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
		ft_print_error("cd", NULL, "too many arguments", 1);
	else if (!dir)
		chdir(getenv("HOME"));
	else if(open(dir, O_RDONLY | __O_DIRECTORY) == -1)
		ft_print_error("cd", dir, "Not a directory", 1);
	else if(access(dir, F_OK) == 0)
		chdir(dir);
	else if(!ft_strnstr(tmpdir, "//", ft_strlen(tmpdir)) && access(tmpdir, F_OK) == 0)
		chdir(tmpdir);
	else
		ft_print_error("cd", dir, "No such file or directory", 1);
	free (dir);
	free_change_dir(cwd, tmpdir);
}
