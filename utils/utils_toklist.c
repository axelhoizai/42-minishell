/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_toklist.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoizai <ahoizai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 17:28:09 by ahoizai           #+#    #+#             */
/*   Updated: 2025/02/22 17:50:47 by ahoizai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_tok	*ms_lstlast(t_tok *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

static t_tok	*ms_lst_sndlast(t_tok *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next->next)
		lst = lst->next;
	return (lst);
}

t_tok	*ms_lstnew(int type, char *str, bool quotes)
{
	t_tok	*new_element;

	new_element = (t_tok *)malloc(sizeof(t_tok));
	if (!new_element)
		return (NULL);
	new_element->type = type;
	new_element->str = str;
	new_element->quotes = quotes;
	if (!new_element->str)
	{
		free(new_element);
		return (NULL);
	}
	new_element->next = NULL;
	return (new_element);
}

void	ms_lstadd_back(t_tok **lst, t_tok *new)
{
	t_tok	*last;

	if (lst && new)
	{
		if (*lst == NULL)
		{
			*lst = new;
			(*lst)->prev = NULL;
		}
		else
		{
			last = ms_lstlast(*lst);
			last->next = new;
			new->prev = last;
		}
	}
}

int	ms_lstsize(t_tok *lst)
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