/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdemare <mdemare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 09:35:18 by mdemare           #+#    #+#             */
/*   Updated: 2024/10/29 16:22:02 by mdemare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (lst && f)
	{
		while (lst)
		{
			f(lst->content);
			lst = lst->next;
		}
	}
}
/* void	print_content(void *content)
{
	printf("%s\n", (char *)content);
}

int	main(void)
{
	t_list	*elem1 = ft_lstnew("Hello");
	t_list	*elem2 = ft_lstnew("World");
	t_list	*elem3 = ft_lstnew("42");

	elem1->next = elem2;
	elem2->next = elem3;

	ft_lstiter(elem1, print_content);
	free(elem1);
	free(elem2);
	free(elem3);
	return (0);
} 
// cc -Wall -Wextra -Werror ft_lstiter_bonus.c ft_lstnew_bonus.c
*/
