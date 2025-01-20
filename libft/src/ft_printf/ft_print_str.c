/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdemare <mdemare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 13:52:21 by mdemare           #+#    #+#             */
/*   Updated: 2024/12/08 16:03:25 by mdemare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

int	ft_print_str(char *s)
{
	size_t	len;

	len = 0;
	if (s)
	{
		len = ft_strlen(s);
		write(1, s, len);
	}
	else
	{
		write(1, "(null)", 6);
		len = 6;
	}
	return (len);
}
