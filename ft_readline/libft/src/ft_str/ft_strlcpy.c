/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdemare <mdemare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 10:12:30 by mdemare           #+#    #+#             */
/*   Updated: 2024/10/29 16:23:09 by mdemare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = 0;
	while (src[len])
		len++;
	if (size == 0)
		return (len);
	if (!dst || !src)
		return (0);
	while (src[i] != '\0' && i < (size - 1))
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (len);
}
/* int 	main(void)
{
	size_t size = 10;
	char	strlcpyDest[] = "strlcpyDest";
	char	strlcpySrc[] = "strlcpySrc";
	char src[] = "coucou";
	char dest[10];

	printf("ft_strlcpy = %zu \n", ft_strlcpy(strlcpyDest, strlcpySrc, size));
	printf("strlcpy = %zu \n\n", strlcpy(strlcpyDest, strlcpySrc, size));
	ft_memset(dest, 'A', 10);
	printf("dest = %s\n", dest);
	printf("ft_strlcpy2 = %zu , len = %lu, dest[0] = %c\n",
	 	ft_strlcpy(dest, src, 0), ft_strlen(src), dest[0]);
	printf("strlcpy2 = %zu , len = %lu, dest[0] = %c\n",
		strlcpy(dest, src, 0), ft_strlen(src), dest[0]);
	return (0);
} */
