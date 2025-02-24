/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_trim_whitespace.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoizai <ahoizai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 01:11:46 by mdemare           #+#    #+#             */
/*   Updated: 2025/02/24 20:57:29 by ahoizai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

char	*ft_trim_whitespace(const char *str)
{
	char	*trimmed_start;
	char	*str_trimmed;

	if (!str)
		return (NULL);
	trimmed_start = ft_trim_start_whitespace(str);
	if (!trimmed_start)
		return (NULL);
	str_trimmed = ft_trim_end_whitespace(trimmed_start);
	free(trimmed_start);
	return (str_trimmed);
}
