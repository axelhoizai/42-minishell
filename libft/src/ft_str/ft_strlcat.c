/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdemare <mdemare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 13:54:37 by mdemare           #+#    #+#             */
/*   Updated: 2024/10/29 16:23:06 by mdemare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dstlen;
	size_t	srclen;
	size_t	i;
	size_t	result;

	dstlen = ft_strlen(dst);
	srclen = ft_strlen(src);
	i = 0;
	if (size > dstlen)
		result = srclen + dstlen;
	else
		result = srclen + size;
	while (src[i] && (dstlen + 1) < size)
	{
		dst[dstlen] = src[i];
		dstlen++;
		i++;
	}
	dst[dstlen] = '\0';
	return (result);
}
/* int		main(void)
{
	size_t size = 14;
	char	strlcatDest[] = "strlcatDest";
	char	strlcatSrc[] = "strlcatSrc";
	char	strlcatDest2[] = "strlcatDest";
	char	strlcatSrc2[] = "strlcatSrc";
	
	printf("ft_strlcat = %zu \n", ft_strlcat(strlcatDest, strlcatSrc, size));
	printf("strlcat = %zu \n", strlcat(strlcatDest2, strlcatSrc2, size));
	return (0);
} */
