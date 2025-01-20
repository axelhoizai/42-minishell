/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdemare <mdemare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 09:01:25 by mdemare           #+#    #+#             */
/*   Updated: 2024/10/29 16:22:33 by mdemare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*d;
	const unsigned char	*s;

	i = 0;
	d = (unsigned char *)dest;
	s = (const unsigned char *)src;
	if ((!d && !s))
		return (NULL);
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dest);
}
/* int	main(void)
{
	char	memcpyDest[] = "Hello World";
	char	*memcpySrc = "Yoooo";
	char	memcpyDest2[] = "Hello World";
	char	*memcpySrc2 = "Yoooo";
	size_t size = 5;
	char *result = ft_memcpy(memcpyDest, memcpySrc, size);
	char *result2 = memcpy(memcpyDest2, memcpySrc2, size);
	
	printf("ft_memcpy = %s \n", result);
	printf("memcpy = %s \n", result2);
	return (0);
} */
