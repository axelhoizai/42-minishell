/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdemare <mdemare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 09:35:50 by mdemare           #+#    #+#             */
/*   Updated: 2024/10/29 16:22:07 by mdemare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*new_elem;
	void	*new_content;

	if (!lst || !f || !del)
		return (NULL);
	new_list = NULL;
	while (lst)
	{
		new_content = f(lst->content);
		if (!new_content)
			return (ft_lstclear(&new_list, del), NULL);
		new_elem = ft_lstnew(new_content);
		if (!new_elem)
		{
			del(new_content);
			return (ft_lstclear(&new_list, del), NULL);
		}
		ft_lstadd_back(&new_list, new_elem);
		lst = lst->next;
	}
	return (new_list);
}
/* void	*to_upper(void *content)
{
	char	*str = (char *)content;
	char	*new_str;
	int		i = 0;

	new_str = strdup(str);
	if (!new_str)
		return (NULL);
	while (new_str[i])
	{
		if (new_str[i] >= 'a' && new_str[i] <= 'z')
			new_str[i] -= 32;
		i++;
	}
	return (new_str);
}

int main(void)
{
	t_list	*elem1 = ft_lstnew(strdup("hello"));
	t_list	*elem2 = ft_lstnew(strdup("world"));
	t_list	*elem3 = ft_lstnew(strdup("42"));

	elem1->next = elem2;
	elem2->next = elem3;
	t_list	*new_list = ft_lstmap(elem1, &to_upper, &free);
	t_list	*tmp = new_list;
	while (tmp)
	{
		printf("%s\n", (char *)tmp->content);
		tmp = tmp->next;
	}
	ft_lstclear(&elem1, &free);
	ft_lstclear(&new_list, &free);

	return (0);
}
// cc -Wall -Wextra -Werror ft_lstmap_bonus.c ft_lstnew_bonus.c 
// ft_lstclear_bonus.c ft_lstadd_back_bonus.c ft_lstdelone_bonus.c 
// ft_lstlast_bonus.c */
