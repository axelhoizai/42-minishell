/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline_free.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalicem <kalicem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 15:42:15 by mdemare           #+#    #+#             */
/*   Updated: 2025/02/12 22:43:18 by kalicem          ###   ########.fr       */
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
	int i;
	if (!rl)
		return;
	free_term(rl);
	// free_history(rl);
	// if (rl->buffer)
	// {
	// 	free(rl->buffer);
	// 	rl->buffer = NULL;
	// }
	if (rl->lines)
	{
		i = 0;
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

void	free_var(void *var)
{
	if (!var)
		return;
	if (var)
	{
		free(var);
		var = NULL;
	}
}

void	free_tab(char **tab)
{
	int i;

	if (!tab)
		return;
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		tab[i] = NULL;
		i++;
	}
	free(tab);
	tab = NULL;
}
