/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoizai <ahoizai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 11:02:47 by mdemare           #+#    #+#             */
/*   Updated: 2025/02/17 17:29:02 by ahoizai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	print_export(t_env_ms *lst)
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

static void	add_var(char *key, char **argv, t_data *data)
{
	int		i;

	i = 1;
	while (argv[i] && argv[i][0] != '$')
	{
		key = get_envkey(argv[i]);
		if (!ms_find(data->env_ms, key))
		{
			if (ft_strchr(argv[i], '='))
			{
				ms_lstadd_back(&(data->env_ms),
					ms_lstnew(get_envkey(argv[i]),
						get_envval(argv[i]), true));
			}
			else
			{
				ms_lstadd_back(&(data->env_ms),
					ms_lstnew(get_envkey(argv[i]),
						get_envval(argv[i]), false));
			}
		}
		free(key);
		i++;
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
		add_var(key, argv, data);
		lst_to_tab(data->env_ms, data);
	}
}

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
