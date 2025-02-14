/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline_arrow.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdemare <mdemare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 15:16:12 by mdemare           #+#    #+#             */
/*   Updated: 2025/02/14 14:57:01 by mdemare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	move_cursor_up(t_rl *rl)
{
	int		new_pos;
	ssize_t	previous_line_length;

	if (!rl || rl->term->cursor_row == rl->prompt_row)
		return;
	new_pos = rl->cursor_pos - rl->term->term_col;
	if (new_pos < 0)
		new_pos = 0;
	previous_line_length = 0;
	while (new_pos + previous_line_length < rl->line_length &&
		   previous_line_length < rl->term->term_col &&
		   rl->buffer[new_pos + previous_line_length] != '\n')
		previous_line_length++;
	if (new_pos > 0 && rl->buffer[new_pos - 1] == '\n')
		new_pos--;
	if (rl->term->cursor_row - 1 == rl->prompt_row)
	{
		previous_line_length += rl->prompt_len + 1;
		new_pos += rl->prompt_len + 1;
	}
	rl->cursor_pos = new_pos;
	rl->term->cursor_row--;
	write(STDOUT_FILENO, "\033[A", 3);
	if (previous_line_length >= rl->term->term_col)
		previous_line_length = rl->term->term_col;
	printf("\033[%ldG", previous_line_length);
	fflush(stdout);
	rl->term->cursor_col = previous_line_length;
}

void	move_cursor_down(t_rl *rl)
{
	rl->term->cursor_col = 0;
	rl->term->cursor_row += 1;
	write(STDOUT_FILENO, "\033[B", 3);
	printf("\033[%uG", 0);
}

void	move_cursor_left(t_rl *rl) //ok
{
	if (rl->cursor_pos < 0)
		return;
	if (rl->term->cursor_row == rl->prompt_row)
	{
		if (rl->term->cursor_col > rl->prompt_len + 1)
		{
			rl->term->cursor_col -= 1;
			write(STDOUT_FILENO, "\033[D", 3);
		}
	}
	else if (rl->term->cursor_col > 0)
	{
		rl->term->cursor_col -= 1;
		write(STDOUT_FILENO, "\033[D", 3);
	}
	if (rl->term->cursor_col == 0)
		move_cursor_up(rl);
	recalculate_cursor_line_pos(rl);
	rl->cursor_limit_line = false;
}

void	move_cursor_right(t_rl *rl)
{
	if (rl->cursor_pos == rl->line_length && rl->cursor_limit_line == false)
	{
		rl->term->cursor_col += 1;
		rl->cursor_limit_line = true;
	}
	else if (rl->cursor_pos == rl->line_length && rl->cursor_limit_line == true)
		return ;
	if (rl->term->cursor_col == (ssize_t)(rl->term->term_col))
		move_cursor_down(rl);
	else if(rl->cursor_pos <= rl->line_length)
	{
		rl->term->cursor_col += 1;
		rl->cursor_pos++;
		write(STDOUT_FILENO, "\033[C", 3);
	}
	recalculate_cursor_line_pos(rl);
}

void	handle_history(t_rl *rl, int direction)
{
	int		i;
	char	*history_entry;

	if (!rl || !rl->history || rl->history->history_count == 0)
		return ;
	
	move_cursor(rl->prompt_row, rl->prompt_len);
	rl->term->cursor_col += 1;
	write(STDOUT_FILENO, "\033[C", 3);
	printf("\033[J");
	if (direction == ARROW_UP && rl->history->history_index > 0)
		rl->history->history_index--;
	else if (direction == ARROW_DOWN &&
			rl->history->history_index < rl->history->history_count - 1)
		rl->history->history_index++;
	else
	{
		ft_bzero(rl->buffer, rl->buffer_size);
		return ;
	}
	ft_bzero(rl->buffer, rl->buffer_size);
	rl->line_length = 0;
	rl->cursor_pos = 0;
	// printf("\033[%dH\033[%dG%s\033[J", rl->prompt_row, rl->prompt_col, rl->prompt);
	history_entry = rl->history->history_tab[rl->history->history_index];
	i = 0;
	while (history_entry[i])
		insert_char_at_cursor(rl, history_entry[i++]);
}
