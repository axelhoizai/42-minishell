/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline_input.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdemare <mdemare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 15:31:18 by mdemare           #+#    #+#             */
/*   Updated: 2025/02/11 09:52:21 by mdemare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	handle_enter(t_rl *rl, int bytes_available, char c)
{
	if (bytes_available == 0)
	{
		parse_historique(rl->buffer, rl->history);
		write(1, "\n", 1);
		// Vérifier si on a assez de place pour ajouter '\n'
		// if (rl->line_length + 1 >= rl->buffer_size)
		// 	rl->buffer = ft_realloc(rl->buffer, rl->buffer_size *= 2);

		// // Ajouter '\n' à la fin du buffer
		// rl->buffer[rl->line_length] = '\n';
		// rl->line_length++;
		// rl->buffer[rl->line_length] = '\0';
		return (1);
	}
	else
	{
		if (rl->line_length >= rl->buffer_size - 1)
			rl->buffer = ft_realloc(rl->buffer, rl->buffer_size *= 2);
		rl->buffer[rl->line_length] = '\n';
		rl->line_length++;
		rl->buffer[rl->line_length] = '\0';
		while (bytes_available > 0)
		{
			read(STDIN_FILENO, &c, 1);
			if (rl->line_length >= rl->buffer_size - 1)
				rl->buffer = ft_realloc(rl->buffer, rl->buffer_size *= 2);
			rl->buffer[rl->line_length] = c;
			rl->line_length++;
			rl->buffer[rl->line_length] = '\0';
			ioctl(STDIN_FILENO, FIONREAD, &bytes_available);
		}
	}
	return (0);
}

void	handle_delete(t_rl *rl)
{
	if (!rl || !rl->buffer || rl->cursor_pos >= rl->line_length)
		return;

	ft_memmove(rl->buffer + rl->cursor_pos,
			   rl->buffer + rl->cursor_pos + 1,
			   rl->line_length - rl->cursor_pos);
	rl->line_length--;
	rl->buffer[rl->line_length] = '\0';
	write(STDOUT_FILENO, "\033[s", 3);
	write(STDOUT_FILENO, rl->buffer + rl->cursor_pos, rl->line_length - rl->cursor_pos);
	write(STDOUT_FILENO, " ", 1);
	write(STDOUT_FILENO, "\033[u", 3);
}

void	handle_backspace(t_rl *rl)
{
	// int	tmp_col;

	if (!rl || !rl->buffer || rl->line_length == 0 || rl->cursor_pos < 0)
		return;
	// tmp_col = 0;
	ft_memmove(rl->buffer + rl->cursor_pos - 1,
			   rl->buffer + rl->cursor_pos,
			   rl->line_length - rl->cursor_pos);
	rl->cursor_pos--;
	rl->line_length--;
	rl->buffer[rl->line_length] = '\0';

	// tmp_col = rl->term->cursor_col;
	move_cursor_left(rl);
	write(STDOUT_FILENO, " \b", 2);
	if (rl->line_length && rl->cursor_pos && rl->cursor_pos == rl->line_length)
		get_cursor_position(rl);
	// // write(STDOUT_FILENO, " \b", 2);
	// write(STDOUT_FILENO, rl->buffer + rl->cursor_pos, rl->line_length - rl->cursor_pos);
	// write(STDOUT_FILENO, " ", 1);

	// if (rl->line_length > 0)
	// 	move_cursor(rl->term->cursor_row, tmp_col);
	// else if (rl->line_length == 0)
	// {
	// 	write(STDOUT_FILENO, "\b", 1);
	// 	write(STDOUT_FILENO, "\033[C", 3);
	// }
}

void	insert_char_at_cursor(t_rl *rl, char c)
{
	if (!rl || !rl->buffer || rl->cursor_pos >= rl->buffer_size - 1)
	rl->temp_prompt_row = rl->prompt_row;
	if (rl->line_length >= rl->buffer_size - 1)
		rl->buffer = ft_realloc(rl->buffer, rl->buffer_size *= 2);
	ft_memmove(rl->buffer + rl->cursor_pos + 1,
			   rl->buffer + rl->cursor_pos,
			   rl->line_length - rl->cursor_pos);
	rl->buffer[rl->cursor_pos] = c;
	rl->cursor_pos++;
	rl->line_length++;
	rl->buffer[rl->line_length] = '\0';
	if (detect_scroll(rl))
		rl->term->cursor_row--;
	write(STDOUT_FILENO, "\033[s", 3);
	write(STDOUT_FILENO, rl->buffer + rl->cursor_pos - 1, rl->line_length - rl->cursor_pos + 1);
	write(STDOUT_FILENO, "\033[u", 3);
	if (rl->term->cursor_col>= (ssize_t)rl->term->term_col)
	{

		rl->term->cursor_col = 1;
		rl->term->cursor_row++;
		write(STDOUT_FILENO, "\033[C", 3);
		write(STDOUT_FILENO, "\n", 1);
	}
	else
	{
		rl->term->cursor_col++;
		write(STDOUT_FILENO, "\033[C", 3);
	}
}

void	handle_arrow_keys(t_rl *rl, char first_char)
{
	char	seq[3];

	if (first_char == ESC)
	{
		if (read(STDIN_FILENO, &seq[0], 1) <= 0)
			return ;
		if (read(STDIN_FILENO, &seq[1], 1) <= 0)
			return ;
		if (seq[0] == '[')
		{
			if (seq[1] == '3')
			{
				if (read(STDIN_FILENO, &seq[2], 1) <= 0)
					return;
				if (seq[2] == '~')
					handle_delete(rl);
				return ;
			}
			get_cursor_position(rl);
			if (seq[1] == ARROW_LEFT)
				move_cursor_left(rl);
			else if (seq[1] == ARROW_RIGHT)
				move_cursor_right(rl);
			else if (seq[1] == ARROW_UP || seq[1] == ARROW_DOWN)
				handle_history(rl, seq[1]);
		}
	}
}
