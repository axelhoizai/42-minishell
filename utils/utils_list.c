/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoizai <ahoizai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 16:28:38 by ahoizai           #+#    #+#             */
/*   Updated: 2025/02/18 11:03:58 by ahoizai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_env_ms	*ms_lstlast(t_env_ms *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

t_env_ms	*ms_lstnew(char *env_key, char *env_value, bool equal_sign)
{
	t_env_ms	*new_element;

	new_element = (t_env_ms *)malloc(sizeof(t_env_ms));
	if (!new_element)
		return (NULL);
	new_element->key = env_key;
	new_element->value = env_value;
	new_element->equal_sign = equal_sign;
	if (!new_element->key)
	{
		free(new_element);
		return (NULL);
	}
	new_element->next = NULL;
	return (new_element);
}

void	ms_lstadd_back(t_env_ms **lst, t_env_ms *new)
{
	t_env_ms	*last;

	if (lst && new)
	{
		if (*lst == NULL)
			*lst = new;
		else
		{
			last = ms_lstlast(*lst);
			last->next = new;
		}
	}
}

int	ms_lstsize(t_env_ms *lst)
{
	int	count;

	count = 0;
	while (lst)
	{
		lst = lst->next;
		count++;
	}
	return (count);
}
