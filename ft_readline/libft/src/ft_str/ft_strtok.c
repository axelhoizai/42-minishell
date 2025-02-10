/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdemare <mdemare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 14:12:56 by mdemare           #+#    #+#             */
/*   Updated: 2025/02/10 19:10:01 by mdemare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

char	*ft_strtok(char *str, const char *delim)
{
	static char	*remainder;
	char		*token;

	if (str != NULL)
		remainder = str;
	if (remainder == NULL)
		return (NULL);
	while (*remainder && ft_strchr(delim, *remainder))
		remainder++;
	if (*remainder == '\0')
		return (NULL);
	token = remainder;
	while (*remainder && !ft_strchr(delim, *remainder))
		remainder++;
	if (*remainder != '\0')
	{
		*remainder = '\0';
		remainder++;
	}
	return (token);
}

// int	main(int argc, char **argv)
// {
// 	char	*token;

// 	if (argc == 3)
// 	{
// 		token = ft_strtok(argv[1], argv[2]);
// 		while (token != NULL)
// 		{
// 			printf("token = %s\n", token);
// 			token = ft_strtok(NULL, argv[2]);
// 		}
// 	}
// 	return (0);
// }