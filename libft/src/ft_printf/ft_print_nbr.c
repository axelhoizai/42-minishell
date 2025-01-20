/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_nbr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdemare <mdemare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 13:52:43 by mdemare           #+#    #+#             */
/*   Updated: 2024/12/08 15:59:54 by mdemare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

static int	ft_numlen(int n)
{
	int	len;

	len = 0;
	if (n <= 0)
		len++;
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}

int	ft_print_nbr(int n)
{
	int	len;

	len = ft_numlen(n);
	if (n == -2147483648)
	{
		write(1, "-2147483648", 11);
		return (len);
	}
	if (n < 0)
	{
		write(1, "-", 1);
		n = -n;
	}
	if (n >= 10)
		ft_print_nbr(n / 10);
	ft_print_char((n % 10) + '0');
	return (len);
}
