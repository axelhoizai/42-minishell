/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdemare <mdemare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 14:20:13 by mdemare           #+#    #+#             */
/*   Updated: 2024/10/29 16:21:32 by mdemare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}
/* int	main(void)
{
	int	num = 'a';
	if (ft_isdigit(num))
		printf("%c %s", num, "is digit\n");
	else
		printf("%c %s", num, "no digit\n");
	return (0);
} */
