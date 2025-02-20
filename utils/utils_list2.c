/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_list2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoizai <ahoizai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 16:27:45 by ahoizai           #+#    #+#             */
/*   Updated: 2025/02/20 19:32:03 by ahoizai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ms_lstclear(t_env_ms **lst)
{
	t_env_ms	*temp;

	if (!lst || !*lst)
		return ;
	while (*lst)
	{
		temp = (*lst)->next;
		if ((*lst)->key)
			free((*lst)->key);
		if ((*lst)->value)
			free((*lst)->value);
		free(*lst);
		*lst = temp;
	}
}

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
	tmp = NULL;
}

void	lst_to_tab(t_env_ms *lst, t_data *data)
{
	int			i;
	t_env_ms	*tmp;
	char		*key;

	i = 0;
	tmp = lst;
	if (data->my_envp)
		free_tab(data->my_envp);
	data->my_envp = NULL;
	data->my_envp = malloc (sizeof (char *) * (ms_lstsize(lst) + 1));
	if (!data->my_envp)
		return ;
	while (tmp)
	{
		key = ft_strjoin(tmp->key, "=");
		data->my_envp[i] = ft_strjoin(key, tmp->value);
		free (key);
		i++;
		tmp = tmp->next;
	}
	data->my_envp[i] = NULL;
}
