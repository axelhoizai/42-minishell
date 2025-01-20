/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdemare <mdemare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 15:26:34 by mdemare           #+#    #+#             */
/*   Updated: 2024/10/29 16:21:20 by mdemare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

int	ft_isalnum(int c)
{
	if ((c >= '0' && c <= '9')
		|| (c >= 'a' && c <= 'z')
		|| (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}
/* int	main(void)
{
	int		alnum = 'b';
	if (ft_isalnum(alnum))
		printf("%c %s", alnum, "is alnum\n");
	else
		printf("%c %s", alnum, "no alnum\n");
	return (0);
} */
