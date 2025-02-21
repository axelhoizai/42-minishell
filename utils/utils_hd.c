/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_hd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoizai <ahoizai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 13:24:24 by ahoizai           #+#    #+#             */
/*   Updated: 2025/02/21 13:26:21 by ahoizai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	is_hd(t_pipeline *pip)
{
	int	i;

	i = 0;
	while (pip->cmds[i])
	{
		if (pip->cmds[i]->limiters)
			return (true);
		i++;
	}
	return (false);
}

int	limiter_count(t_pipeline *pip)
{
	int		i;
	int		j;
	int		lim_cnt;

	lim_cnt = 0;
	i = 0;
	while (pip->cmds[i])
	{
		j = 0;
		while (pip->cmds[i]->limiters && pip->cmds[i]->limiters[j])
		{
			lim_cnt++;
			j++;
		}
		i++;
	}
	return (lim_cnt);
}
