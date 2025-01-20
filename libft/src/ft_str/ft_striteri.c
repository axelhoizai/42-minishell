/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdemare <mdemare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 18:15:25 by mdemare           #+#    #+#             */
/*   Updated: 2024/10/29 16:23:02 by mdemare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	if (!s || !f)
		return ;
	i = 0;
	while (s[i])
	{
		f(i, &s[i]);
		i++;
	}
}
/* void	ft_tolower_test(unsigned int i, char *c)
{
	(void)i;
	if (*c >= 'A' && *c <= 'Z')
		*c = ft_tolower(*c);
}
int		main(void)
{
	char	*s1 = "Hello, World!";
	char	*s2 = ft_strdup(s1);
	
	ft_striteri(s2, ft_tolower_test);
	printf("teststriteri : s1 = %s\nresult = %s\n", s1, s2);
	free(s2);
	return (0);
}
// cc -g -Wall -Wextra -Werror ft_striteri.c ft_tolower.c ft_strdup.c */
