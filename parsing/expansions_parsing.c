/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions_parsing.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalicem <kalicem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 23:20:33 by mdemare           #+#    #+#             */
/*   Updated: 2025/01/24 23:36:18 by kalicem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*merge_args(char *current, const char *str, int start, int end)
{
	char	*new_part;
	char	*merged;

	new_part = ft_substr(str, start, end - start);
	if (!new_part)
		return (NULL);
	if (!current)
		return (new_part);
	merged = ft_strjoin(current, new_part);
	free(current);
	free(new_part);
	return (merged);
}

int	handle_quotes(const char *str, int *index, char quote)
{
	int	start;

	(*index)++;
	start = *index;
	while (str[*index] && str[*index] != quote)
		(*index)++;
	if (str[*index] == quote)
		(*index)++;
	else
	{
		ft_print_error("echo", NULL, "syntax error with open quotes", 2);
		return (-1);
	}
	return (start);
}

int	parse_quoted_arg(const char *str, int *i, char **current_arg)
{
	int		start;

	start = handle_quotes(str, i, str[*i]);
	if (start == -1)
		return (-1);
	*current_arg = merge_args(*current_arg, str, start, *i - 1);
	if (!*current_arg)
		return (-1);
	return (0);
}

int	parse_unquoted_arg(const char *str, int *i, char **current_arg)
{
	int		start;

	start = *i;
	while (str[*i] && !ft_isspace(str[*i])
		&& str[*i] != '\'' && str[*i] != '"')
		(*i)++;
	*current_arg = merge_args(*current_arg, str, start, *i);
	if (!*current_arg)
		return (-1);
	return (0);
}
