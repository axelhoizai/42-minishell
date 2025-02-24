/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_trim_start_whitespace.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoizai <ahoizai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 01:10:29 by mdemare           #+#    #+#             */
/*   Updated: 2025/02/24 20:57:38 by ahoizai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

char	*ft_trim_start_whitespace(const char *str)
{
	int		i;
	char	*trimmed_str;

	if (!str)
		return (NULL);
	i = 0;
	while (str[i] && ft_isspace(str[i]))
		i++;
	trimmed_str = ft_strdup(str + i);
	if (!trimmed_str)
		return (NULL);
	return (trimmed_str);
}
