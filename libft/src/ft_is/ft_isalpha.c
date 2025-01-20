/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdemare <mdemare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 13:51:54 by mdemare           #+#    #+#             */
/*   Updated: 2024/10/29 16:21:26 by mdemare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

int	ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}
/* int	main(void)
{
	int		alpha = '1';
	if (ft_isalpha(alpha))
		printf("%c %s", alpha, "is alpha\n");
	else
		printf("%c %s", alpha, "no alpha\n");
	return (0);
} */
