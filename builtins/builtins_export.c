/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdemare <mdemare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 11:02:47 by mdemare           #+#    #+#             */
/*   Updated: 2025/01/25 15:14:58 by mdemare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// void	export_var(t_env_ms *lst, char **argv)
// {
	
// }

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
			ft_printf("declare -x %s=\"%s\"\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
}

void	ft_export(char **argv)
{
	char	*key;

	key = NULL;
	if (ft_strcmp(argv[0], "export") == 0 && !argv[1])
		print_export(data.env_ms);
	else if (ft_strcmp(argv[0], "export") == 0 && argv[1] && argv[1][0] != '$')
	{
		key = get_env_key(argv[1]);
		if (!ms_find(data.env_ms, key))
			ms_lstadd_back(&(data.env_ms), ms_lstnew(get_env_key(argv[1]), get_env_value(argv[1])));
		free(key);
	}
}

