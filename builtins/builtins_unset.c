/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_unset.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoizai <ahoizai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 11:03:10 by mdemare           #+#    #+#             */
/*   Updated: 2025/02/25 18:22:25 by ahoizai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_unset(char **argv, t_data *data)
{
	int		i;
	char	*key;

	if (!ft_strcmp(argv[0], "export"))
	{
		i = 1;
		while (argv[i])
		{
			key = get_envkey(argv[i]);
			ms_lstdelone(&data->env_ms, key);
			free(key);
			i++;
		}
	}
	else if (argv[1])
	{
		i = 1;
		while (argv[i])
		{
			ms_lstdelone(&data->env_ms, argv[i]);
			i++;
		}
	}
	lst_to_tab(data->env_ms, data);
}
