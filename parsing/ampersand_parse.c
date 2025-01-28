/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_ampersand_parse.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalicem <kalicem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 20:41:56 by mdemare           #+#    #+#             */
/*   Updated: 2025/01/28 20:43:46 by kalicem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*process_ampersand_parts(char *arg, int i)
{
	char	*tmp1;
	char	*tmp2;
	char	*tmp3;

	tmp1 = ft_substr(arg, 0, i);
	tmp2 = ft_strdup("\n");
	tmp3 = ft_strjoin(tmp1, tmp2);
	free(tmp1);
	free(tmp2);
	tmp1 = ft_substr(arg, i + 3, ft_strlen(arg) - (i + 3));
	tmp2 = ft_strjoin(tmp3, tmp1);
	free(tmp1);
	free(tmp3);
	return (tmp2);
}

static int	find_double_ampersand(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (i > 0 && arg[i + 1] && arg[i + 2] && arg[i - 1] == ' '
			&& arg[i] == '&' && arg[i + 1] == '&' && arg[i + 2] == ' ')
			return (i);
		i++;
	}
	return (-1);
}

char	*replace_double_ampersand(char *arg)
{
	char	*tmp;
	int		i;

	if (!arg)
		return (NULL);
	i = find_double_ampersand(arg);
	if (i == -1)
		return (arg);
	tmp = process_ampersand_parts(arg, i);
	free(arg);
	arg = ft_strdup(tmp);
	free(tmp);
	if (ft_strstr(arg, "$?"))
		return (replace_double_ampersand(arg));
	return (arg);
}
