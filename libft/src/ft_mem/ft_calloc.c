/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdemare <mdemare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 14:21:41 by mdemare           #+#    #+#             */
/*   Updated: 2024/10/29 16:22:26 by mdemare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*ptr;
	size_t	total_size;

	if (size == 0 || nmemb == 0)
		return (malloc(0));
	total_size = nmemb * size;
	if (total_size / nmemb != size)
		return (NULL);
	ptr = malloc(total_size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, total_size);
	return (ptr);
}
/* int		main(void)
{
	int	i;
	int	*pointer;

	pointer = (int *)calloc(12, sizeof(int));
	i = 0;
	if	(!pointer)
		return (1);	
	while (i < 12 - 1)
	{
		pointer[i] = i;
		i++;
	}
	i = 0;
	printf("test malloc : ");
	while (i < 12)
	{
		printf("%d ", pointer[i]);
		i++;
	}
	printf("\n");
	free(pointer);
	return (0);
} */
