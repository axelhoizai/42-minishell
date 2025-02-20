/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup_tab.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdemare <mdemare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 12:50:02 by mdemare           #+#    #+#             */
/*   Updated: 2025/02/20 12:50:27 by mdemare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

char	**ft_strdup_tab(char **args)
{
	char	**new_args;
	int		i;
	int		count;

	count = 0;
	while (args[count])
		count++;
	new_args = ft_calloc(sizeof(char *) * (count + 1), 1);
	if (!new_args)
		return (NULL);
	i = 0;
	while (i < count)
	{
		new_args[i] = ft_strdup(args[i]);
		if (!new_args[i])
		{
			while (i > 0)
				free(new_args[--i]);
			free(new_args);
			return (NULL);
		}
		i++;
	}
	new_args[count] = NULL;
	return (new_args);
}
