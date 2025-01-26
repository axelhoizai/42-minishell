/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing_echo.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalicem <kalicem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 16:29:48 by mdemare           #+#    #+#             */
/*   Updated: 2025/01/26 15:13:32 by kalicem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*handle_n(char *flag)
{
	int		i;

	i = 1;
	if (ft_strcmp("-n", flag) != 0 && flag[0] == '-')
	{
		while (flag[i] && flag[i] == 'n')
			i++;
		if (flag[i] == '\0')
			return (ft_strdup("-n"));
	}
	return (NULL);
}
