/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_unset.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoizai <ahoizai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 11:03:10 by mdemare           #+#    #+#             */
/*   Updated: 2025/02/20 19:27:37 by ahoizai          ###   ########.fr       */
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
		lst_to_tab(data->env_ms, data);
	}
	else if (argv[1])
	{
		i = 1;
		while (argv[i])
		{
			printf("argv[%d] : %s\n", i, argv[i]);
			ms_lstdelone(&data->env_ms, argv[i]);
			i++;
		}
		lst_to_tab(data->env_ms, data);
	}
}
