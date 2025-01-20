/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdemare <mdemare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 08:20:02 by mdemare           #+#    #+#             */
/*   Updated: 2024/10/29 16:22:28 by mdemare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*str;

	str = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (str[i] == (unsigned char)c)
			return ((void *)(str + i));
		i++;
	}
	return (NULL);
}
/* int	main(void)
{
	const	char *strmemchr = "test";
	int	intmemchr = 'e';
	size_t	sizememchr = 4;
	char	*resultmemchr = ft_memchr(strmemchr, intmemchr, sizememchr);
	
	printf("ft_memchr = char : %c first pos: %ld in : %s\n", 
		intmemchr, resultmemchr - strmemchr, strmemchr);

	printf("ft_memchr = %p\n",ft_memchr(strmemchr, intmemchr, sizememchr));
	printf("memchr = %p\n",memchr(strmemchr, intmemchr, sizememchr));
	return (0);
} */
