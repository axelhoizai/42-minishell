/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdemare <mdemare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 16:28:38 by ahoizai           #+#    #+#             */
/*   Updated: 2025/01/27 10:55:04 by mdemare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env_ms	*ms_lstnew(char *env_key, char *env_value)
{
	t_env_ms	*new_element;

	new_element = (t_env_ms *)malloc(sizeof(t_env_ms));
	if (!new_element)
		return (NULL);
	new_element->key = env_key;
	new_element->value = env_value;
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

t_env_ms	*ms_lstlast(t_env_ms *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
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
	char		*swap_key;
	char		*swap_value;

	tmp = lst;
	while (lst && lst->next)
	{
		if (ft_strcmp(lst->key, lst->next->key) > 0)
		{
			swap_key = lst->key;
			lst->key = lst->next->key;
			lst->next->key = swap_key;
			swap_value = lst->value;
			lst->value = lst->next->value;
			lst->next->value = swap_value;
			swap_value = lst->value;
			lst = tmp;
		}
		else
			lst = lst->next;
	}
	return (tmp);
}

void	ms_lstclear(t_env_ms **lst)
{
	t_env_ms	*temp;

	if (!lst || !*lst)
		return;
	while (*lst)
	{
		temp = (*lst)->next;
		if ((*lst)->key)
			free((*lst)->key);
		if ((*lst)->value)
			free((*lst)->value);
		free(*lst);
		*lst = temp;
	}
	*lst = NULL;
}
