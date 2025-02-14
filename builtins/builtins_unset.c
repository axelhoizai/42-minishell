/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_unset.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdemare <mdemare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 11:03:10 by mdemare           #+#    #+#             */
/*   Updated: 2025/02/14 18:59:35 by mdemare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//! Not pushed, removed leaks
void	ft_unset(int argc, char **argv, t_pipeline *pip, t_data *data)
{
	int	i;

	(void)argc;
	(void)pip;
	if (argv[1])
	{
		i = 1;
		while (argv[i])
			ms_lstdelone(&data->env_ms, argv[i++]);
		lst_to_tab(data->env_ms, data);
	}
}
