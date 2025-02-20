/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_endwith.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdemare <mdemare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 17:19:45 by mdemare           #+#    #+#             */
/*   Updated: 2025/02/20 17:22:54 by mdemare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

int	ft_str_endwith(const char *str, const char *set)
{
	int	str_len;
	int	set_len;

	if (!str || !set || !*str || !*set)
		return (0);
	str_len = ft_strlen(str);
	set_len = ft_strlen(set);
	if (str_len < set_len)
		return (0);
	return (ft_strncmp(str + str_len - set_len, set, set_len) == 0);
}
