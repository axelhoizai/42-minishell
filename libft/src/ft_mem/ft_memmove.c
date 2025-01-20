/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdemare <mdemare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 09:26:27 by mdemare           #+#    #+#             */
/*   Updated: 2024/10/29 16:22:35 by mdemare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;
	size_t				i;

	if (dest == src)
		return (dest);
	d = (unsigned char *)dest;
	s = (const unsigned char *)src;
	if (d > s)
	{
		i = n;
		while (i-- > 0)
			d[i] = s[i];
	}
	else
	{
		i = 0;
		while (i < n)
		{
			d[i] = s[i];
			i++;
		}
	}
	return (dest);
}
/* int	main(void)
{
	size_t size = 10;
	char	memmoveDest[] = "memmoveDest";
	char	memmoveSrc[] = "memmoveSrc";
	char	memmoveDest2[] = "memmoveDest";
	char	memmoveSrc2[] = "memmoveSrc";
	
	ft_memmove(memmoveDest, memmoveSrc, size);
	printf("ft_memmove = %s \n", memmoveDest);
	memmove(memmoveDest2, memmoveSrc2, size);
	printf("memmove = %s \n", memmoveDest);
	return (0);
} */
