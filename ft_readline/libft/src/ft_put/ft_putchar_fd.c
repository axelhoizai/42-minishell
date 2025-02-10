/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdemare <mdemare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 18:38:40 by mdemare           #+#    #+#             */
/*   Updated: 2024/10/29 16:22:42 by mdemare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
/* int	main(void)
{
	printf("test ft_putchar_fd :\n");
	char	c = 'c';
	ft_putchar_fd(c, 1);
	return (0);
} */
