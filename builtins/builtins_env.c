/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoizai <ahoizai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 11:03:27 by mdemare           #+#    #+#             */
/*   Updated: 2025/01/24 16:39:30 by ahoizai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_env_ms(t_data *data, char **envp)
{
	int	i;

	i = 0;
	data->env_ms = NULL;
	while (envp[i])
	{
		ms_lstadd_back(&data->env_ms, ms_lstnew(envp[i]));
		i++;
	}
}

void	ft_env(t_data *data)
{
	print_lst(data->env_ms);
}
