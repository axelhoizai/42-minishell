/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdemare <mdemare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 18:39:28 by mdemare           #+#    #+#             */
/*   Updated: 2024/10/29 16:22:48 by mdemare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	if (s)
		write(fd, s, ft_strlen(s));
}
// int	main(void)
// {
// 	printf("test ft_putstr_fd :\n");
// 	char	c[] = "Hello World";
// 	ft_putstr_fd(c, 1);
// 	return (0);
// }
