/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dup_tab_index.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdemare <mdemare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 13:19:42 by mdemare           #+#    #+#             */
/*   Updated: 2025/02/21 17:16:20 by mdemare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

char	**ft_dup_tab_index(char **tab_src, int index)
{
	int		j;
	int		len;
	char	**tab_dest;

	j = 0;
	len = 0;
	while (tab_src[index + len])
		len++;
	tab_dest = malloc(sizeof(char *) * (len + 1));
	if (!tab_dest)
		return (NULL);
	while (tab_src[index + j])
	{
		tab_dest[j] = strdup(tab_src[index + j]);
		j++;
	}
	tab_dest[j] = NULL;
	return (tab_dest);
}
