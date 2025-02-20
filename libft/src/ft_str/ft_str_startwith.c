/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_startwith.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdemare <mdemare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 17:20:17 by mdemare           #+#    #+#             */
/*   Updated: 2025/02/20 17:20:47 by mdemare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

int	ft_str_startwith(const char *str, const char *set)
{
	int	set_len;

	if (!str || !set || !*str || !*set)
		return (0);
	set_len = ft_strlen(set);
	return (ft_strncmp(str, set, set_len) == 0);
}
