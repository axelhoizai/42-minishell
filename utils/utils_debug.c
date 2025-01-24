/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_debug.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoizai <ahoizai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 19:17:22 by mdemare           #+#    #+#             */
/*   Updated: 2025/01/24 19:44:30 by ahoizai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		printf("[%d] : \'%s\'\n", i, tab[i]);
		i++;
	}
}
void	print_lst(t_env_ms *lst)
{
	t_env_ms	*tmp;

	tmp = lst;
	while (tmp)
	{
		ft_printf("%s\n", tmp->env_var);
		tmp = tmp->next;
	}
}
