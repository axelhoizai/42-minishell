/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdemare <mdemare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 18:08:16 by mdemare           #+#    #+#             */
/*   Updated: 2024/10/29 16:22:37 by mdemare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*ptr;

	i = 0;
	ptr = (unsigned char *)s;
	while (i < n)
	{
		ptr[i] = (unsigned char)c;
		i++;
	}
	return (s);
}
/* int	main(void)
{
	char	testmemset[] = "testmemset";
	char	testmemset2[] = "testmemset";
	
	ft_memset(testmemset, '*', 5);
	printf("ft_memset = %s\n", testmemset);
	memset(testmemset2, '*', 5);
	printf("memset = %s\n", testmemset2);
	return (0);
} */
