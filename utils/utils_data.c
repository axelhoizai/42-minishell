/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdemare <mdemare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 14:32:16 by mdemare           #+#    #+#             */
/*   Updated: 2025/02/14 15:27:44 by mdemare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_init(char **envp, int *is_start, t_data *data)
{
	if (*is_start == 0)
	{
		data->exit_code = 0;
		data->is_reading = 0;
		init_env_ms(envp, data);
		*is_start = 1;
		data->term = (t_data_term *)ft_calloc(sizeof(t_data_term), 1);
		if (!data->term)
			return ;
	}
}

t_data	*get_data(t_data *new_data)
{
	static t_data	*data = NULL;

	if (new_data)
		data = new_data;
	return (data);
}
