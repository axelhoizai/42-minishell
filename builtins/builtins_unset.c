/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_unset.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoizai <ahoizai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 11:03:10 by mdemare           #+#    #+#             */
/*   Updated: 2025/02/06 11:35:27 by ahoizai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//! Not pushed, removed leaks
void	ft_unset(int argc, char **argv, t_pipeline *pip, t_data *data)
{
	(void)argc;
	(void)pip;
	int	i;
	
	if (!argv[1])
		printf("");
	else
	{
		i = 1;
		while (argv[i])
			ms_lstdelone(&data->env_ms, argv[i++]);
		lst_to_tab(data->env_ms, data);
	}
	// free_pipeline(pip);
}
