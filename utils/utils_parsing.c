/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdemare <mdemare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 19:13:26 by mdemare           #+#    #+#             */
/*   Updated: 2025/01/22 19:50:17 by mdemare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_count_single(char *arg)
{
	int	count_simgle;
	int	i;
	
	count_simgle = 0;
	i = 0;
	while(arg[i])
	{
		if (arg[i] == '\'')
			count_simgle++;
		i++;
	}
	if (count_simgle % 2 == 1)
		count_simgle -=1;
	return (count_simgle);
}

static int	ft_count_double(char *arg)
{
	int	count_double;
	int	i;
	
	count_double = 0;
	i = 0;
	while(arg[i])
	{
		if (arg[i] == '\"')
			count_double++;
		i++;
	}
	if (count_double % 2 == 1)
		count_double -=1;
	
	return (count_double);
}

char	*parse_quote(char *arg)
{
	char	*tmp1;
	int		j;
	int		count_double;
	int		count_simgle;

	j = 0;
	count_simgle = ft_count_single(arg);
	count_double = ft_count_double(arg);
	tmp1 = ft_calloc(ft_strlen(arg), 1);
	while (arg && *arg)
	{
		while (count_double > 0 && *arg == '"')
		{
			count_double -= 1;
			arg++;
		}
		while (count_simgle > 0 && *arg == '\'')
		{
			count_simgle -= 1;
			arg++;
		}
		tmp1[j++] = *arg;
		arg++;
	}
	return (tmp1);
}
