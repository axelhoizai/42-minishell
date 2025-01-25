/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdemare <mdemare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 14:32:16 by mdemare           #+#    #+#             */
/*   Updated: 2025/01/25 15:50:18 by mdemare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_data data;

void	ft_init(char **envp, int is_start)
{
	if (is_start == 0)
	{
		data.exit_code = 0;
		data.envp = envp;
		init_env_ms(envp);
		is_start = 1;	
	}
}