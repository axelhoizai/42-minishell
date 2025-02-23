/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_tab.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalicem <kalicem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 23:58:53 by mdemare           #+#    #+#             */
/*   Updated: 2025/02/22 23:59:37 by kalicem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

char	*ft_strjoin_tab(char **args, int count)
{
	char	*result;
	char	*temp;
	int		i;

	if (count == 0)
		return (ft_strdup(""));
	result = ft_strdup(args[0]);
	i = 1;
	while (i < count)
	{
		temp = ft_strjoin(result, " ");
		free(result);
		result = ft_strjoin(temp, args[i]);
		free(temp);
		i++;
	}
	return (result);
}
