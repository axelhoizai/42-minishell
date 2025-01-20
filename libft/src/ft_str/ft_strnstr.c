/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdemare <mdemare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 09:05:19 by mdemare           #+#    #+#             */
/*   Updated: 2024/12/08 16:56:42 by mdemare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	if (!*little)
		return ((char *)big);
	i = 0;
	while (big[i] && i < len)
	{
		j = 0;
		while (little[j] && big[i + j]
			&& i + j < len
			&& big[i + j] == little[j])
			j++;
		if (!little[j])
			return ((char *)(big + i));
		i++;
	}
	return (NULL);
}
/* int		main(void)
{
	const	char *big = "hello world";
	const	char *little = "lo";
	
	size_t	sizestrnstr = -1;
	printf("ft_strnstr = %s \n", ft_strnstr(big, little, sizestrnstr));
	printf("strnstr = %s \n", strnstr(big, little, sizestrnstr));
	return (0);
} */
