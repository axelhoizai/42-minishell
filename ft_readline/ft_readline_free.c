/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline_free.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdemare <mdemare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 15:42:15 by mdemare           #+#    #+#             */
/*   Updated: 2025/02/10 19:31:01 by mdemare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_term(t_rl *rl)
{
	if (rl->term)
	{
		free(rl->term);
		rl->term = NULL;	
	}
}

void	free_readline(t_rl *rl)
{
	if (!rl)
		return;
	free_term(rl);
	free_history(rl);
	if (rl->buffer)
	{
		free(rl->buffer);
		rl->buffer = NULL;
	}
	if (rl->lines)
	{
		int i = 0;
		while (i < (int)rl->line_count)
		{
			if (rl->lines[i])
			{
				free(rl->lines[i]);
				rl->lines[i] = NULL;
			}
			i++;
		}
		free(rl->lines);
		rl->lines = NULL;
	}
}
