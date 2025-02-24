/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_trim_end_whitespace.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoizai <ahoizai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 01:11:10 by mdemare           #+#    #+#             */
/*   Updated: 2025/02/24 20:58:05 by ahoizai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

char	*ft_trim_end_whitespace(const char *str)
{
	int		len;
	char	*trimmed_str;

	if (!str)
		return (NULL);
	len = ft_strlen(str);
	while (len > 0 && ft_isspace(str[len - 1]))
		len--;
	trimmed_str = ft_substr(str, 0, len);
	if (!trimmed_str)
		return (NULL);
	return (trimmed_str);
}
