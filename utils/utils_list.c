/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoizai <ahoizai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 16:28:38 by ahoizai           #+#    #+#             */
/*   Updated: 2025/01/24 19:41:25 by ahoizai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env_ms	*ms_lstlast(t_env_ms *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
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

t_env_ms	*ms_lstnew(char *env_var)
{
	t_env_ms	*new_element;

	new_element = (t_env_ms *)malloc(sizeof(t_env_ms));
	if (!new_element)
		return (NULL);
	new_element->env_var = env_var;
	new_element->next = NULL;
	return (new_element);
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

t_env_ms	*sort_list(t_env_ms *lst)
{
	t_env_ms	*tmp;
	char		*swap;

	tmp = lst;
	while (lst && lst->next)
	{
		if (ft_strcmp(lst->env_var, lst->next->env_var) > 0)
		{
			swap = lst->env_var;
			lst->env_var = lst->next->env_var;
			lst->next->env_var = swap;
			lst = tmp;
		}
		else
			lst = lst->next;
	}
	return (tmp);
}
