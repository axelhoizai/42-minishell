/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdemare <mdemare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 17:35:46 by mdemare           #+#    #+#             */
/*   Updated: 2024/12/08 15:59:52 by mdemare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

static int	ft_count_hex_digits(unsigned int number)
{
	int	count;

	if (number == 0)
		return (1);
	count = 0;
	while (number != 0)
	{
		number /= 16;
		count++;
	}
	return (count);
}

int	ft_print_hex(unsigned int number, int upper_case)
{
	char	hex_digits[17];
	int		i;

	i = 0;
	while (i < 16)
	{
		if (i < 10)
			hex_digits[i] = '0' + i;
		else
		{
			if (upper_case == 0)
				hex_digits[i] = 'a' + (i - 10);
			else
				hex_digits[i] = 'A' + (i - 10);
		}
		i++;
	}
	hex_digits[16] = '\0';
	if (number >= 16)
		ft_print_hex((number / 16), upper_case);
	write(1, &hex_digits[number % 16], 1);
	return (ft_count_hex_digits(number));
}
