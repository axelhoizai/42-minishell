/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdemare <mdemare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 15:14:36 by mdemare           #+#    #+#             */
/*   Updated: 2024/10/29 16:22:55 by mdemare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s != '\0')
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if ((char)c == '\0')
		return ((char *)s);
	return (NULL);
}
/* int	main(void)
{
	const	char *strstrchr = "test";
	char	cstrchr = 't';
	char	*resultstrchr = ft_strchr(strstrchr, cstrchr);
	char	*resultstrchr2 = ft_strchr(strstrchr, cstrchr);
	
	printf("ft_strchr = char : %c first pos: %ld in : %s\n", 
		cstrchr, resultstrchr - strstrchr, strstrchr);

	printf("ft_strchr = %s\n", resultstrchr);

	printf("strchr = char : %c first pos: %ld in : %s\n", 
		cstrchr, resultstrchr2 - strstrchr, strstrchr);
	printf("strchr = %s\n", resultstrchr2);
	return (0);
} */
