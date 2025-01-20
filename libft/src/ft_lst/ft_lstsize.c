/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdemare <mdemare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 16:19:29 by mdemare           #+#    #+#             */
/*   Updated: 2024/10/29 16:22:13 by mdemare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

int	ft_lstsize(t_list *lst)
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
/* int	main(void)
{
	t_list	*list;
	int		size;
	t_list	*new_elem;
	t_list	*new_elem2;

	printf("test ft_lstsize :\n");
	list = NULL;
	new_elem = ft_lstnew("Elem 1");
	new_elem2 = ft_lstnew("Elem 2");
	ft_lstadd_front(&list, new_elem);
	ft_lstadd_front(&list, new_elem2);
	size = ft_lstsize(list);
	if (size == 2)
		printf("OK: Size is correct\n");
	else
		printf("Error: Size is incorrect\n");
	free(new_elem);
	free(new_elem2);
	return (0);
} */
