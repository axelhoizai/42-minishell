/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalicem <kalicem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 11:02:47 by mdemare           #+#    #+#             */
/*   Updated: 2025/01/25 10:30:21 by kalicem          ###   ########.fr       */
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
		if (ft_strncmp(lst->env_var, var, ft_strlen(var)) == 0)
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
		if (strncmp(tmp->env_var, "_=", 2) != 0)
			ft_printf("export %s\n", tmp->env_var);
		tmp = tmp->next;
	}
}

void	ft_export(t_env_ms *lst, char **argv)
{
	if (ft_strcmp(argv[0], "export") == 0 && !argv[1])
		print_export(lst);
	else if (ft_strcmp(argv[0], "export") == 0 && argv[1])
	{
		if (!ms_find(lst, argv[1]))
		{
			ms_lstadd_back(&lst, ms_lstnew(argv[1]));
			// print_export(lst);
		}
	}
}

