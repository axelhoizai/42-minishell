/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdemare <mdemare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 13:42:30 by mdemare           #+#    #+#             */
/*   Updated: 2025/02/13 16:10:43 by mdemare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*result;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	result = ft_calloc(((ft_strlen(s1) + ft_strlen(s2)) + 1), 1);
	if (!result)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		result[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		result[i + j] = s2[j];
		j++;
	}
	result[i + j] = '\0';
	return (result);
}
/* int		main(void)
{
	char *s1 = "Hello, ";
	char *s2 = "World!";
	char *result = ft_strjoin(s1, s2);
	
	printf("ft_strjoin : s1 = %s\ns2 = %s\nres= %s\n", s1, s2, result);
	free(result);
	return (0);
} */
