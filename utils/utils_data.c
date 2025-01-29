/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdemare <mdemare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 14:32:16 by mdemare           #+#    #+#             */
/*   Updated: 2025/01/29 17:06:06 by mdemare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_init(char **envp, int *is_start, t_data *data)
{
	if (*is_start == 0)
	{
		data->exit_code = 0;
		init_env_ms(envp, data);
		*is_start = 1;
	}
}
