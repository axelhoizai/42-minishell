/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoizai <ahoizai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 11:02:47 by mdemare           #+#    #+#             */
/*   Updated: 2025/02/01 17:55:46 by ahoizai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//? Check if an env key exists
bool	is_key(t_env_ms *lst, char *var)
{
	while (lst)
	{
		if (ft_strcmp(lst->key, var) == 0)
			return (true);
		lst = lst->next;
	}
	return (false);
}

//? Find the node linked to the env key
t_env_ms	*ms_find(t_env_ms *lst, char *var)
{
	while (lst)
	{
		if (ft_strcmp(lst->key, var) == 0)
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}

void	print_export(t_env_ms *lst)
{
	t_env_ms	*tmp;

	tmp = sort_list(lst);
	while (tmp)
	{
		if (strcmp(tmp->key, "_") != 0)
		{
			if (tmp->equal_sign == true)
				ft_printf("export %s=\"%s\"\n", tmp->key, tmp->value);
			else
				ft_printf("export %s\n", tmp->key);
		}
		tmp = tmp->next;
	}
}

void	ft_export(char **argv, t_data *data)
{
	char	*key;
	
	key = NULL;
	if (ft_strcmp(argv[0], "export") == 0 && !argv[1])
		print_export(data->env_ms);
	else if (ft_strcmp(argv[0], "export") == 0 && argv[1] && argv[1][0] != '$')
	{
		key = get_envkey(argv[1]);
		if (!ms_find(data->env_ms, key))
		{
			if (ft_strchr(argv[1], '='))
			{
				ms_lstadd_back(&(data->env_ms),
					ms_lstnew(get_envkey(argv[1]), get_envval(argv[1]), true));
			}
			else
			{
				ms_lstadd_back(&(data->env_ms),
					ms_lstnew(get_envkey(argv[1]), get_envval(argv[1]), false));
			}
		}
		free(key);
		lst_to_tab(data->env_ms, data);
	}
}
