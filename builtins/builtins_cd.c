/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdemare <mdemare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 09:56:34 by mdemare           #+#    #+#             */
/*   Updated: 2025/02/26 17:16:47 by mdemare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	free_change_dir(t_pipeline *pip, char *cwd, char *tmpdir, char *tmp)
{
	(void)pip;
	if (cwd)
		free(cwd);
	if (tmpdir)
		free(tmpdir);
	if (tmpdir)
		free (tmp);
}

static int	check_dir(char	*dir)
{
	int		fd;
	int		result;

	result = 0;
	fd = open(dir, O_RDONLY | __O_DIRECTORY);
	if (fd == -1)
		result = -1;
	if (fd >= 0)
		close(fd);
	return (result);
}

static int	handle_cd_error(int argc, char *dir, t_data *data)
{
	if (argc > 2)
	{
		data->exit_code = 1;
		ft_print_error("cd", NULL, "too many arguments");
		return (0);
	}
	else if (!dir)
	{
		chdir(getenv("HOME"));
		return (0);
	}
	else if (check_dir(dir) == -1)
	{
		data->exit_code = 1;
		files_checker(dir, data);
		if (data->exit_code > 2)
			data->exit_code = 1;
		return (0);
	}
	return (1);
}

static void	ft_chdir(char *path)
{
	update_oldpwd();
	chdir(path);
}

void	change_dir(int argc, char **argv, t_pipeline *pip, t_data *data)
{
	char	*tmp;
	char	*dir;
	char	*tmpdir;
	char	*cwd;

	tmp = NULL;
	dir = argv[1];
	if (dir)
		tmp = ft_strdup(dir);
	cwd = getcwd(NULL, 0);
	tmpdir = ft_strjoin(cwd, tmp);
	if (handle_cd_error(argc, dir, data) == 1)
	{
		if (access(dir, F_OK) == 0)
			ft_chdir(dir);
		else if (!ft_strnstr(tmpdir, "//", ft_strlen(tmpdir))
			&& access(tmpdir, F_OK) == 0)
			ft_chdir(tmpdir);
		else
		{
			data->exit_code = 1;
			ft_print_error("cd", dir, "No such file or directory");
		}
	}
	free_change_dir(pip, cwd, tmpdir, tmp);
}
