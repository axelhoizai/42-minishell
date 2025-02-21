/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_wildcard.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdemare <mdemare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 09:37:28 by mdemare           #+#    #+#             */
/*   Updated: 2025/02/21 17:31:16 by mdemare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sort_args(char **args, int count, int i, int j)
{
	char	*tmp;
	char	*tmp_i;
	char	*tmp_j;

	while (i < count - 1)
	{
		j = i + 1;
		while (j < count)
		{
			tmp_i = ft_strdup(args[i]);
			tmp_j = ft_strdup(args[j]);
			ft_str_tolower(tmp_i);
			ft_str_tolower(tmp_j);
			if (ft_strcmp(tmp_i, tmp_j) > 0)
			{
				tmp = args[i];
				args[i] = args[j];
				args[j] = tmp;
			}
			free(tmp_i);
			free(tmp_j);
			j++;
		}
		i++;
	}
}

static int	match_wildcard(const char *pattern, const char *filename)
{
	while (*pattern && *filename)
	{
		if (*pattern == '*')
		{
			pattern++;
			if (!*pattern)
				return (1);
			while (*filename)
				if (match_wildcard(pattern, filename++))
					return (1);
			return (0);
		}
		else if (*pattern != *filename)
			return (0);
		pattern++;
		filename++;
	}
	return (*pattern == *filename);
}

static void	get_wildcard(char **args, DIR *dir, int *files_cnt, char **new_args)
{
	struct dirent	*entry;
	int				i;
	int				j;

	i = 0;
	j = 0;
	while (args[i])
	{
		if (ft_strchr(args[i], '*'))
		{
			entry = readdir(dir);
			while (entry == readdir(dir))
			{
				if (entry->d_name[0] != '.'
					&& match_wildcard(args[i], entry->d_name))
					new_args[j++] = ft_strdup(entry->d_name);
			}
			(*files_cnt) = j;
		}
		else
			new_args[j++] = ft_strdup(args[i]);
		i++;
	}
	new_args[j] = NULL;
}

static bool	check_wildcard(char **args)
{
	int		i;
	bool	has_wildcard;

	i = 0;
	has_wildcard = false;
	while (args[i])
	{
		if (ft_strchr(args[i], '*'))
		{
			has_wildcard = true;
			break ;
		}
		i++;
	}
	return (has_wildcard);
}

char	**expand_wildcard(char **args)
{
	DIR		*dir;
	char	**new_args;
	int		files_count;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!check_wildcard(args))
		return (args);
	dir = opendir(".");
	if (!dir)
		return (args);
	new_args = ft_safe_malloc(sizeof(char *) * 1024);
	if (!new_args)
		return (args);
	files_count = 0;
	get_wildcard(args, dir, &files_count, new_args);
	if (files_count > 0)
		sort_args(new_args + 1, files_count - 1, i, j);
	free_tab(args);
	closedir(dir);
	return (new_args);
}
