/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_unset.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoizai <ahoizai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 11:03:10 by mdemare           #+#    #+#             */
/*   Updated: 2025/01/27 15:25:13 by ahoizai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


void	ms_lstdelone(t_env_ms **lst, char *env_key)
{
	t_env_ms	*tmp;
	t_env_ms	*del_tmp;

	tmp = *lst;
	while (tmp && tmp->next)
	{
		if (ft_strcmp(tmp->next->key, env_key) == 0)
		{
			free(tmp->next->key);
			free(tmp->next->value);
			del_tmp = tmp->next;
			tmp->next = tmp->next->next;
			free (del_tmp);
		}
		tmp = tmp->next;
	}
	tmp->next = NULL;
}

void	ft_unset(int argc, char *argv)
{
	(void)argc;
	ms_lstdelone(&g_data.env_ms, argv);
}
