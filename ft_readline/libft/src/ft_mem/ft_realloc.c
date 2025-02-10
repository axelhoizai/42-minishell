/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalicem <kalicem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 20:37:16 by mdemare           #+#    #+#             */
/*   Updated: 2025/02/08 00:39:32 by kalicem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

void	*ft_realloc(void *ptr, size_t size)
{
	size_t	i;
	char	*new_ptr;
	char	*old_ptr;

	if (ptr == 0)
	{
		free(ptr);
		return (NULL);
	}
	new_ptr = (char *)ft_calloc(1, size);
	if (!new_ptr)
		return (NULL);
	if (!ptr)
		return (new_ptr);
	old_ptr = (char *)ptr;
	i = 0;
	while (old_ptr[i] && i < size)
	{
		new_ptr[i] = old_ptr[i];
		i++;
	}
	free(ptr);
	return ((void *)new_ptr);
}
