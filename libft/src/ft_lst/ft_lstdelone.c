/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdemare <mdemare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 08:54:41 by mdemare           #+#    #+#             */
/*   Updated: 2024/10/29 16:21:42 by mdemare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (lst && del)
	{
		del(lst->content);
		free(lst);
	}
}
/* int	main(void)
{
	t_list	*node = malloc(sizeof(t_list));
	
	if (node)
	{
		node->content = malloc(10 * sizeof(char));
		if (!node->content)
			free(node);
		ft_lstdelone(node, free);
	}
} */
