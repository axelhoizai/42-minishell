/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdemare <mdemare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 14:44:31 by mdemare           #+#    #+#             */
/*   Updated: 2024/10/29 16:23:30 by mdemare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

static int	ft_in_set(char c, const char *set)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;

	end = 0;
	if (!s1 || !set)
		return (NULL);
	start = 0;
	while (s1[start] && ft_in_set(s1[start], set))
		start++;
	end = ft_strlen(s1);
	while (end > start && ft_in_set(s1[end - 1], set))
		end--;
	return (ft_substr(s1, start, end - start));
}
/* int		main(void)
{
	char	*s1 = "   Hello, World!  ";
	char	*set = " ";
	char	*result = ft_strtrim(s1, set);
	
	printf("strtrim s1 = \"%s\"\nset = \"%s\" \nres= \"%s\"\n",
	s1, set, result);
	free(result);
	return (0);
}
// cc -g -Wall -Wextra -Werror ft_strtrim.c 
//ft_strlen.c ft_substr.c ft_strdup.c */
