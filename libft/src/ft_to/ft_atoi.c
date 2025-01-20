/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdemare <mdemare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 09:52:03 by mdemare           #+#    #+#             */
/*   Updated: 2024/10/29 16:23:36 by mdemare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

int	ft_atoi(const char *nptr)
{
	long	i;
	long	j;
	long	number;
	int		signe;

	i = 0;
	j = 0;
	number = 0;
	signe = 1;
	while ((nptr[i] == ' ' || (nptr[i] >= '\t' && nptr[i] <= '\r')))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i++] == '-')
			signe = -1;
	}
	while (nptr[i] == '0')
		i++;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		number = number * 10 + (nptr[i++] - '0');
		j++;
	}
	return (number * signe);
}
// int	main(void)
// {
// 	char	*str = "\t\n\r\v1474899999999999\n\t\v\f\r+101";
// 	printf("resultat ft_atoi = %d\n", ft_atoi(str));
// 	printf("resultat atoi = %d\n", atoi(str));
// 	return (0);
// }
