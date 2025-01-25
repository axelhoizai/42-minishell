/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdemare <mdemare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 09:56:34 by mdemare           #+#    #+#             */
/*   Updated: 2025/01/25 11:14:27 by mdemare          ###   ########.fr       */
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

char	*parse_dir(char *dir)
{
	char	*tmp1;

	tmp1 = parse_quote(dir);
	if (tmp1 == NULL)
		return (dir);
	else
		return (tmp1);
}

void	change_dir(int argc, char *dir)
{
	char 	*tmp;
	char	*tmpdir;
	char	*cwd;
	int 	fd;

	fd = open(dir, O_RDONLY | __O_DIRECTORY);
	tmpdir = NULL;
	tmp = NULL;
	if (dir)
		tmp = ft_strdup(dir);
	printf("dir = %s\n", tmp);
	cwd = getcwd(NULL, 0);
	tmpdir = ft_strjoin(cwd, tmp);
	if (argc > 2)
		ft_print_error("cd", NULL, "too many arguments", 1);
	else if (!dir)
		chdir(getenv("HOME"));
	else if (fd == -1)
		ft_print_error("cd", dir, "Not a directory", 1);
	else if (access(dir, F_OK) == 0)
		chdir(dir);
	else if (!ft_strnstr(tmpdir, "//", ft_strlen(tmpdir))
		&& access(tmpdir, F_OK) == 0)
		chdir(tmpdir);
	else
		ft_print_error("cd", dir, "No such file or directory", 1);
	if (fd >=0)
		close(fd);
	free (tmp);
	free_change_dir(cwd, tmpdir);
}
