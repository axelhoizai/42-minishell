/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hex_to_uint.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdemare <mdemare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 16:20:49 by mdemare           #+#    #+#             */
/*   Updated: 2024/12/17 16:21:14 by mdemare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

unsigned int	ft_hex_to_uint(const char *hex)
{
	unsigned int	result;
	int				i;
	char			c;

	result = 0;
	i = 0;
	if (hex[0] == '0' && (hex[1] == 'x' || hex[1] == 'X'))
		i = 2;
	while (hex[i] != '\0')
	{
		c = hex[i];
		result *= 16;
		if (c >= '0' && c <= '9')
			result += (c - '0');
		else if (c >= 'a' && c <= 'f')
			result += (c - 'a' + 10);
		else if (c >= 'A' && c <= 'F')
			result += (c - 'A' + 10);
		else
			break ;
		i++;
	}
	return (result);
}
