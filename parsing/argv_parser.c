/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argv_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalicem <kalicem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 23:18:58 by mdemare           #+#    #+#             */
/*   Updated: 2025/01/24 23:35:53 by kalicem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	add_argument(char **args, int *argc, char *arg)
{
	args[*argc] = ft_strdup(arg);
	if (!args[*argc])
		return (-1);
	(*argc)++;
	return (0);
}

static int	add_current_arg(char **args, int *argc, char **current_arg)
{
	if (add_argument(args, argc, *current_arg) == -1)
		return (-1);
	free(*current_arg);
	*current_arg = NULL;
	return (0);
}

static int	process_argument(const char *str, char **args, int *i, int *argc)
{
	char	*current_arg;

	current_arg = NULL;
	while (str[*i] && ft_isspace(str[*i]))
		(*i)++;
	if (!str[*i])
		return (0);
	if (str[*i] == '\'' || str[*i] == '"')
	{
		if (parse_quoted_arg(str, i, &current_arg) == -1)
			return (-1);
	}
	else
	{
		if (parse_unquoted_arg(str, i, &current_arg) == -1)
			return (-1);
	}
	if ((!str[*i] || ft_isspace(str[*i])) && current_arg)
	{
		if (add_current_arg(args, argc, &current_arg) == -1)
			return (-1);
	}
	return (0);
}

char	**parse_args(const char *str)
{
	char	**args;
	int		argc;
	int		i;

	args = ft_calloc(ft_strlen(str) + 1, sizeof(char *));
	if (!args)
		return (NULL);
	argc = 0;
	i = 0;
	while (str[i])
	{
		if (process_argument(str, args, &i, &argc) == -1)
			return (free_tab(args), NULL);
	}
	return (args);
}
