/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdemare <mdemare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 09:34:47 by mdemare           #+#    #+#             */
/*   Updated: 2024/10/29 16:21:41 by mdemare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*temp;

	if (lst && del)
	{
		while (*lst)
		{
			temp = (*lst)->next;
			ft_lstdelone(*lst, del);
			*lst = temp;
		}
	}
}
/* int	main(void)
{
	t_list	*lst;
	t_list	*new_elem;
	char	*str;

	lst = NULL;
	str = ft_strdup("first");
	new_elem = ft_lstnew(str);
	ft_lstadd_back(&lst, new_elem);

	str = ft_strdup("second");
	new_elem = ft_lstnew(str);
	ft_lstadd_back(&lst, new_elem);

	ft_lstclear(&lst, free);

	if (lst == NULL)
		printf("testlstclear: OK\n");
	else
		printf("testlstclear: KO\n");
	return (0);
} */
/* cc -Wall -Wextra -Werror ft_lstadd_back_bonus.c ft_strdup.c 
ft_lstnew_bonus.c ft_lstdelone_bonus.c ft_lstlast_bonus.c ft_lstclear_bonus.c */