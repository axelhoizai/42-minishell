/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_expand_wildcard.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalicem <kalicem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 09:37:28 by mdemare           #+#    #+#             */
/*   Updated: 2025/02/23 01:20:00 by kalicem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sort_args(char **args, int count)
{
	char	*tmp_i;
	char	*tmp_j;
	int		i;
	int		j;

	i = 0;
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
				ft_swap(args[i], args[j]);
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

static void	get_wildcard(char **pattern, DIR *dir, int *count, char **matches)
{
	struct dirent	*entry;

	entry = readdir(dir);
	while (entry)
	{
		if (entry->d_name[0] != '.' && match_wildcard(*pattern, entry->d_name))
		{
			if (*count >= MAX_FILES - 1)
				break ;
			matches[(*count)++] = ft_strdup(entry->d_name);
		}
		entry = readdir(dir);
	}
	closedir(dir);
}

static void	expand_single_wildcard(char **pattern)
{
	DIR				*dir;
	char			**matches;
	char			*result;
	int				count;

	dir = opendir(".");
	if (!dir)
		return ;
	matches = ft_calloc(sizeof(char *) * MAX_FILES, 1);
	if (!matches)
	{
		closedir(dir);
		return ;
	}
	count = 0;
	get_wildcard(pattern, dir, &count, matches);
	if (count > 0)
	{
		sort_args(matches, count);
		result = ft_strjoin_tab(matches, count);
		free(*pattern);
		*pattern = result;
	}
	free_tab(matches);
}

void	expand_wildcard(char **str)
{
	char	**args;
	char	**expanded;
	char	*result;
	int		i;

	args = ft_split(*str, ' ');
	if (!args)
		return ;
	expanded = ft_calloc(sizeof(char *) * MAX_FILES, 1);
	if (!expanded)
		return (free_tab(args));
	i = 0;
	while (args[i])
	{
		if (ft_strchr(args[i], '*'))
			expand_single_wildcard(&args[i]);
		expanded[i] = args[i];
		i++;
	}
	expanded[i] = NULL;
	result = ft_strjoin_tab(expanded, i);
	free(*str);
	*str = result;
	free(expanded);
	free_tab(args);
}
