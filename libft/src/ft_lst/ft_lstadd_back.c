/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdemare <mdemare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 16:59:13 by mdemare           #+#    #+#             */
/*   Updated: 2024/10/29 16:21:37 by mdemare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (lst && new)
	{
		if (*lst == NULL)
			*lst = new;
		else
		{
			last = ft_lstlast(*lst);
			last->next = new;
		}
	}
}
/* int	main(void)
{
	t_list	*list;
	t_list	*new_elem;

	printf("test ft_lstadd_back :\n");
	list = ft_lstnew("Elem 1");
	new_elem = ft_lstnew("Last element");
	ft_lstadd_back(&list, new_elem);
	if (ft_lstlast(list) == new_elem)
		printf("OK: Element added at the back\n");
	else
		printf("Error: Element not added correctly\n");
	free(list);
	free(new_elem);
	return (0);
} */
// cc -Wall -Wextra -Werror ft_lstadd_back_bonus.c 
// ft_lstlast_bonus.c ft_lstnew_bonus.c
