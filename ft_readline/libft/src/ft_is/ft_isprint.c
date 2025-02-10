/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdemare <mdemare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 15:49:21 by mdemare           #+#    #+#             */
/*   Updated: 2024/10/29 16:21:34 by mdemare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

int	ft_isprint(int c)
{
	if (c >= ' ' && c <= '~')
		return (1);
	return (0);
}
/* int	main(void)
{
	int	print = '\r';
	if (ft_isprint(print))
		printf("%c %s", print, "is print\n");
	else
		printf("%c %s", print, "no print\n");
	return (0);
} */
