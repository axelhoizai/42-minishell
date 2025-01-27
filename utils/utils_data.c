/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoizai <ahoizai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 14:32:16 by mdemare           #+#    #+#             */
/*   Updated: 2025/01/27 17:39:40 by ahoizai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_data	g_data;

void	ft_init(char **envp, int is_start)
{
	if (is_start == 0)
	{
		g_data.exit_code = 0;
		init_env_ms(envp);
		is_start = 1;
	}
}
