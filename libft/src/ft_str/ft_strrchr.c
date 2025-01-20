/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdemare <mdemare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 15:15:49 by mdemare           #+#    #+#             */
/*   Updated: 2024/10/29 16:23:26 by mdemare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const char	*last;

	last = NULL;
	while (*s != '\0')
	{
		if (*s == (char)c)
			last = (char *)s;
		s++;
	}
	if ((char)c == '\0')
		return ((char *)s);
	return ((char *)last);
}
/* int		main(void)
{
	const	char *strstrrchr = "test";
	char	cstrrchr = 't';
	char	*resultstrrchr = ft_strrchr(strstrrchr, cstrrchr);
	char	*resultstrrchr2 = ft_strrchr(strstrrchr, cstrrchr);
	
	printf("ft_strrchr = char : %c last pos: %ld in : %s\n", 
		cstrrchr, resultstrrchr - strstrrchr, strstrrchr);

	printf("ft_strrchr = %s\n", resultstrrchr);

	printf("strrchr = char : %c last pos: %ld in : %s\n",
		cstrrchr, resultstrrchr2 - strstrrchr, strstrrchr);
	printf("strrchr = %s\n", resultstrrchr2);
	return (0);
} */
