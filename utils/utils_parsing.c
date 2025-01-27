/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdemare <mdemare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 19:13:26 by mdemare           #+#    #+#             */
/*   Updated: 2025/01/27 10:54:58 by mdemare          ###   ########.fr       */
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

char	*replace_double_ampersand(char *arg)
{
	char	*tmp1;
	char	*tmp2;
	char	*tmp3;
	int		i;

	if (!arg)
		return (NULL);
	i = 0;
	while (arg[i])
	{
		if (i > 0 && arg[i + 1] && arg[i + 2] && arg[i - 1] == ' '
			&& arg[i] == '&' && arg[i + 1] == '&' && arg[i + 2] == ' ')
			break ;
		i++;
	}
	if (!arg[i])
		return (arg);
	tmp1 = ft_substr(arg, 0, i);
	tmp2 = ft_strdup("\n");
	tmp3 = ft_strjoin(tmp1, tmp2);
	free(tmp1);
	free(tmp2);
	tmp1 = ft_substr(arg, i + 3, ft_strlen(arg) - (i + 3));
	tmp2 = ft_strjoin(tmp3, tmp1);
	free(arg);
	arg = ft_strdup(tmp2);
	free(tmp1);
	free(tmp2);
	free(tmp3);
	if (ft_strstr(arg, "$?"))
		return (replace_double_ampersand(arg));
	return (arg);
}
