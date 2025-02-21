/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoizai <ahoizai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 11:27:04 by ahoizai           #+#    #+#             */
/*   Updated: 2025/02/21 11:28:11 by ahoizai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	is_key(t_env_ms *lst, char *var)
{
	while (lst)
	{
		if (ft_strcmp(lst->key, var) == 0)
			return (true);
		lst = lst->next;
	}
	return (false);
}

t_env_ms	*ms_find(t_env_ms *lst, char *var)
{
	while (lst)
	{
		if (ft_strcmp(lst->key, var) == 0)
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}

int	find_index(char *str)
{
	int	i;

	i = 0;
	if (!ft_strcmp(str, "="))
		return (1);
	if (str[0] == '=')
		return (ft_strlen(str));
	while (str[i])
	{
		if (str[i] == '=')
			return (i);
		i++;
	}
	return (i);
}
