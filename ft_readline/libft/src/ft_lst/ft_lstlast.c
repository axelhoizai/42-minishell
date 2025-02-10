/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdemare <mdemare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 16:50:07 by mdemare           #+#    #+#             */
/*   Updated: 2024/10/29 16:22:05 by mdemare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}
/* int	main(void)
{
	t_list	*list;
	t_list	*last;

	printf("test ft_lstlast :\n");
	list = ft_lstnew("Elem 1");
	ft_lstadd_front(&list, ft_lstnew("Elem 2"));
	last = ft_lstlast(list);
	if (last && ft_strncmp(last->content, "Elem 1", 8) == 0)
		printf("OK: Last element is correct\n");
	else
		printf("Error: Last element is incorrect\n");
	free(list);
	free(last);
	return (0);
}
// cc -Wall -Wextra -Werror ft_lstlast_bonus.c 
// ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_strncmp.c */
