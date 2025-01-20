/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_ptr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdemare <mdemare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 14:40:04 by mdemare           #+#    #+#             */
/*   Updated: 2024/12/08 16:00:03 by mdemare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

static int	ft_count_hex_digits(unsigned long number)
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

int	ft_print_ptr(unsigned long ptr, int first)
{
	char	hex_digits[17];
	int		i;

	i = 0;
	while (i < 16)
	{
		if (i < 10)
			hex_digits[i] = '0' + i;
		else
			hex_digits[i] = 'a' + (i - 10);
		i++;
	}
	hex_digits[16] = '\0';
	if (first == 1 && ptr != 0)
		write(1, "0x", 2);
	if (ptr >= 16)
		ft_print_ptr((ptr / 16), 0);
	if (ptr == 0 && ft_count_hex_digits(ptr) <= 1)
	{
		write(1, "(nil)", 5);
		return (5);
	}
	else
		write(1, &hex_digits[ptr % 16], 1);
	return (ft_count_hex_digits(ptr) + 2);
}
