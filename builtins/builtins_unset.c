/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_unset.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoizai <ahoizai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 11:03:10 by mdemare           #+#    #+#             */
/*   Updated: 2025/02/03 15:52:32 by ahoizai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//! Not pushed, removed leaks
void	ft_unset(int argc, char **argv, t_pipeline *pip, t_data *data)
{
	(void)argc;
	(void)pip;
	if (!argv[1])
		printf("");
	else
	{
		ms_lstdelone(&data->env_ms, argv[1]);
		lst_to_tab(data->env_ms, data);
	}
	// free_pipeline(pip);
}
