/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdemare <mdemare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 11:16:11 by mdemare           #+#    #+#             */
/*   Updated: 2024/10/29 16:22:09 by mdemare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new_element;

	new_element = (t_list *)malloc(sizeof(t_list));
	if (!new_element)
		return (NULL);
	new_element->content = content;
	new_element->next = NULL;
	return (new_element);
}
/* int	main(void)
{
	char	*content = "Hello, World!";
	t_list *node;

	node = ft_lstnew(content);
	printf("test ft_lstnew :\n");
	if (node == NULL)
		printf("Error: Node creation failed\n");
	if (node->content == content)
		printf("Content is correct: %s\n", (char *)node->content);
	else
		printf("Error: Content is incorrect\n");
	if (node->next == NULL)
		printf("Next pointer is NULL as expected\n");
	else
		printf("Error: Next pointer is not NULL\n");
	free(node);
	return (0);
} */
