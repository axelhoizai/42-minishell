/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_list2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalicem <kalicem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 16:27:45 by ahoizai           #+#    #+#             */
/*   Updated: 2025/01/28 20:47:00 by kalicem          ###   ########.fr       */
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
	*lst = NULL;
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
	tmp->next = NULL;
}

void	lst_to_tab(t_env_ms *lst)
{
	int			i;
	t_env_ms	*tmp;
	char		*key;

	i = 0;
	tmp = lst;
	if (g_data.my_envp)
		free_tab(g_data.my_envp);
	g_data.my_envp = NULL;
	g_data.my_envp = malloc (sizeof (char *) * (ms_lstsize(lst) + 1));
	if (!g_data.my_envp)
		return ;
	while (tmp)
	{
		key = ft_strjoin(tmp->key, "=");
		g_data.my_envp[i] = ft_strjoin(key, tmp->value);
		free (key);
		tmp = tmp->next;
		i++;
	}
	g_data.my_envp[i] = NULL;
}
