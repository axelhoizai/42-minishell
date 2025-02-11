/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_safe_malloc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalicem <kalicem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 00:30:53 by mdemare           #+#    #+#             */
/*   Updated: 2025/02/09 02:35:43 by kalicem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"
#include <signal.h>

void	*ft_safe_malloc(size_t size)
{
	struct sigaction	old_action;
	struct sigaction	new_action;
	void				*ptr;

	if (size == 0)
		return (NULL);
	ft_memset(&new_action, 0, sizeof(struct sigaction));
	new_action.sa_handler = SIG_IGN;
	if (sigaction(SIGINT, &new_action, &old_action) == -1)
		return (NULL);
	ptr = malloc(size);
	if (!ptr)
	{
		sigaction(SIGINT, &old_action, NULL);
		return (NULL);
	}
	if (sigaction(SIGINT, &old_action, NULL) == -1)
	{
		free(ptr);
		return (NULL);
	}
	return (ptr);
}
