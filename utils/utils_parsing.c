/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdemare <mdemare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 19:13:26 by mdemare           #+#    #+#             */
/*   Updated: 2025/01/23 19:48:52 by mdemare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_count_quote(char *arg, char quote)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (arg[i])
	{
		if (arg[i] == quote)
			count++;
		i++;
	}
	return (count);
}

static void	parse_single_quote(char **arg, char *str, int *j, int *count_s)
{
	int	len;

	len = 0;
	while ((*arg + 1)[len] && (*arg + 1)[len] != '\'')
		len++;
	(*arg)++;
	ft_memcpy(str + *j, *arg, len);
	*j += len;
	*arg += len + 1;
	*count_s -= 2;
}

static void	parse_double_quote(char **arg, char *str, int *j, int *count_d)
{
	int	len;

	len = 0;
	while ((*arg + 1)[len] && (*arg + 1)[len] != '"')
		len++;
	(*arg)++;
	ft_memcpy(str + *j, *arg, len);
	*j += len;
	*arg += len + 1;
	*count_d -= 2;
}

char	*parse_quote(char *arg)
{
	char	*str;
	int		j;
	int		count_s;
	int		count_d;

	j = 0;
	count_s = ft_count_quote(arg, '\'');
	count_d = ft_count_quote(arg, '"');
	str = ft_calloc(ft_strlen(arg) + 1, sizeof(char));
	if (!str)
		return (NULL);
	while (arg && *arg)
	{
		while (*arg && *arg != '\'' && *arg != '"')
			str[j++] = *arg++;
		if (*arg == '\'' && (count_s % 2 == 0 || count_s >= 2))
			parse_single_quote(&arg, str, &j, &count_s);
		else if (*arg == '"' && (count_d % 2 == 0 || count_d >= 2))
			parse_double_quote(&arg, str, &j, &count_d);
		else
			str[j++] = *arg++;
	}
	return (str);
}
