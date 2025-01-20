/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdemare <mdemare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 15:40:24 by mdemare           #+#    #+#             */
/*   Updated: 2024/10/29 16:21:29 by mdemare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
		return (1);
	return (0);
}
/* int	main(void)
{
	int		isascii = 211;
	if (ft_isascii(isascii))
		printf("%c %s", isascii, "is isascii\n");
	else
		printf("%c %s", isascii, "no isascii\n");
	return (0);
} */
