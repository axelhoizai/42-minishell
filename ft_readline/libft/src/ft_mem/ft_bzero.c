/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdemare <mdemare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 21:29:03 by mdemare           #+#    #+#             */
/*   Updated: 2024/10/29 16:22:22 by mdemare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*ptr;

	i = 0;
	ptr = (unsigned char *)s;
	while (i < n)
	{
		ptr[i] = '\0';
		i++;
	}
}
// int	main(void)
// {	printf("ft_bzero before = ");
// 	int testbzero[10]   = {7, 7, 7, 7, 7, 7, 7, 7, 7, 7};
// 	int	pos = 0;
//	
// 	while (pos < 10)
// 	{
// 		printf("%d: %d ", (pos + 1), testbzero[pos]);
// 		pos++;
// 	}
// 	bzero(testbzero, (6 * sizeof(int)));
// 	printf("\nft_bzero after = ");
// 	pos = 0;
// 	while (pos < 10)
// 	{
// 		printf("%d: %d ", (pos + 1), testbzero[pos]);
// 		pos++;
// 	}
// 	return (0);
// }
