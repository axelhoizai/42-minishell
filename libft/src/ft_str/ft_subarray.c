/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_subarray.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdemare <mdemare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 18:58:19 by mdemare           #+#    #+#             */
/*   Updated: 2025/02/26 19:15:36 by mdemare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

static void	free_tab_subarray(char **tab)
{
	int	i;

	if (!tab)
		return ;
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		tab[i] = NULL;
		i++;
	}
	free(tab);
	tab = NULL;
}

char	**ft_subarray(char **argv, int start, int end)
{
	char	**subarray;
	int		i;

	if (!argv || start >= end)
		return (NULL);
	subarray = ft_calloc(end - start + 1, sizeof(char *));
	if (!subarray)
		return (NULL);
	i = 0;
	while (start < end)
	{
		subarray[i] = ft_strdup(argv[start]);
		if (!subarray[i])
		{
			free_tab_subarray(subarray);
			return (NULL);
		}
		start++;
		i++;
	}
	subarray[i] = NULL;
	return (subarray);
}
