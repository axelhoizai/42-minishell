/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline_init.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdemare <mdemare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 15:36:58 by mdemare           #+#    #+#             */
/*   Updated: 2025/02/10 19:30:55 by mdemare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_term(t_rl *rl)
{
	rl->term = (t_data_term *)ft_calloc(sizeof(t_data_term), 1);
	if (!rl->term)
	{
		free_readline(rl);
		return ;
	}
	rl->term->cursor_row = 0;
	rl->term->cursor_col = 0;
	rl->term->term_col = 0;
	rl->term->term_row = 80;
}

void	init_history(t_rl *rl)
{
	rl->history = (t_history *)ft_calloc(sizeof(t_history), 1);
	if (!rl->history)
		return ;
	rl->history->history_count = 0;
	rl->history->history_index = 0;
	load_history(rl->history);
}

void	init_readline(t_rl *rl)
{
	rl->buffer_size = 1024;
	rl->cursor_pos = 0;
	rl->cursor_limit_line = 0;
	rl->line_length = 0;
	rl->line_capacity = 10;
	rl->line_count = 0;
	rl->temp_prompt_row = 0;
	rl->prompt_row = 0;
	rl->prompt_col = 0;
	rl->prompt = NULL;
	rl->prompt_len = 15;
	rl->lines_needed = 0;
	rl->buffer = (char *)ft_calloc(rl->buffer_size + 1, 1);
	if (!rl->buffer)
		return ;
	ft_memset(rl->buffer, 0, rl->buffer_size);
	rl->lines = (char **)ft_calloc(sizeof(char *) * rl->line_capacity + 1, 1);
	if (!rl->lines)
	{
		free(rl->buffer);
		return ;
	}
	init_term(rl);
	init_history(rl);
	setup_signal_handlers();
}
