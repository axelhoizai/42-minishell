/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdemare <mdemare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 15:30:02 by mdemare           #+#    #+#             */
/*   Updated: 2024/10/29 16:23:13 by mdemare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*result;
	size_t	i;

	if (!s || !f)
		return (NULL);
	result = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!result)
		return (NULL);
	i = 0;
	while (s[i])
	{
		result[i] = f(i, s[i]);
		i++;
	}
	result[i] = '\0';
	return (result);
}
/* char	ft_toupper_test(unsigned int i, char c)
{
	(void)i;
	return (ft_toupper(c));
}
int		main(void)
{
	char	*s1 = "Hello, World!";
	char	*result = ft_strmapi(s1, ft_toupper_test);
	
	printf("teststrmapi : s1 = %s\nresult = %s\n", s1, result);
	free(result);
	return (0);
} */
