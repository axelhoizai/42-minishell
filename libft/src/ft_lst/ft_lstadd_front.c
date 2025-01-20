/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdemare <mdemare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 12:47:56 by mdemare           #+#    #+#             */
/*   Updated: 2024/10/29 16:21:39 by mdemare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (new)
	{
		new->next = *lst;
		*lst = new;
	}
}
/* int	main(void)
{
	t_list	*list;
	t_list	*new_elem;

	list = NULL;
	new_elem = ft_lstnew("First element");
	ft_lstadd_front(&list, new_elem);
	if (list == new_elem)
		printf("OK: Element added at the front\n");
	else
		printf("Error: Element not added correctly\n");
	free(new_elem);
	return (0);
}
cc -Wall -Wextra -Werror ft_lstadd_front_bonus.c ft_lstnew_bonus.c */
