/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdemare <mdemare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 21:43:46 by mdemare           #+#    #+#             */
/*   Updated: 2024/09/15 23:03:03 by mdemare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>

char	*ft_strstr(char *str, char *to_find);

/* int	main(void)
{
	char	str[100];
	char	str2[100];
	char	to_find[] = "";

	strcpy(str, "Veuillez saisir une ligne de texte contenant le mot");
	printf("Fonction strstr = %s \n", strstr(str, to_find));
	strcpy(str2, "Veuillez saisir une ligne de texte contenant le mot");
	printf("Fonction fr_strstr = %s \n", ft_strstr(str2, to_find));
} */

char	*ft_strstr(char *str, char *to_find)
{
	int	i;
	int	j;

	if (to_find[0] == '\0')
		return (str);
	i = 0;
	while (str[i] != '\0')
	{
		j = 0;
		while (to_find[j] != '\0')
		{
			if (str[i + j] == to_find[j])
				j++;
			else
				break ;
			if (to_find[j] == '\0')
				return (str + i);
		}
		i++;
	}
	return (0);
}
