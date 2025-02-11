/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline_helper.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdemare <mdemare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 15:39:52 by mdemare           #+#    #+#             */
/*   Updated: 2025/02/11 09:52:16 by mdemare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	update_display(t_rl *rl)
{
	if (!rl || !rl->buffer)
		return;
	move_cursor(rl->prompt_row, rl->prompt_col);
	write(STDOUT_FILENO, "\033[K", 3);
	printf("%s", rl->prompt);
	fflush(stdout);
	write(STDOUT_FILENO, rl->buffer, rl->line_length);
	get_cursor_position(rl);
	get_prompt_position(rl);
	get_terminal_size(rl);
}

int	is_real_enter()
{
	int	bytes_available;

	ioctl(STDIN_FILENO, FIONREAD, &bytes_available);
	return (bytes_available == 0);
}

int	detect_scroll(t_rl *rl)
{
	if (!rl || !rl->term)
		return (-1);

	if (rl->temp_prompt_row > rl->prompt_row)
	{
		rl->prompt_row--;
		return (1);
	}
	if (rl->term->cursor_row >= (int)rl->term->term_row + 1)
	{
		rl->prompt_row--;
		return (1);
	}
	return (0);
}

t_rl	*get_rl(t_rl *new_rl)
{
	static t_rl	*rl = NULL;

	if (new_rl)
		rl = new_rl;
	return (rl);
}
