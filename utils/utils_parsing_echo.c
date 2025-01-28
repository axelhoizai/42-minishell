/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing_echo.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoizai <ahoizai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 16:29:48 by mdemare           #+#    #+#             */
/*   Updated: 2025/01/28 12:54:13 by ahoizai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*handle_n(char *flag)
{
	int		i;

	i = 1;
	if (ft_strcmp("-n", flag) != 0 && flag[0] == '-' && flag[1] == 'n')
	{
		while (flag[i] && flag[i] == 'n')
			i++;
		if (flag[i] == '\0')
			return (ft_strdup("-n"));
	}
	return (flag);
}
