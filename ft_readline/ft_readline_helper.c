/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline_helper.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdemare <mdemare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 10:23:59 by mdemare           #+#    #+#             */
/*   Updated: 2025/02/04 10:25:13 by mdemare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_readline(t_rl *readline)
{
	readline->prompt_len = 0;
	readline->prompt = NULL;
	readline->history = (t_history *)malloc(sizeof(t_history));
	if (!readline->history)
		return ;
	readline->history->history_count = 0;
	readline->history->history_index = 0;
	load_history(readline->history);
	readline->term = (t_data_term *)malloc(sizeof(t_data_term));
	if (!readline->term)
	{
		free_readline(readline);
		return ;
	}
	save_terminal_settings(readline->term);
	setup_signals();
	readline->prompt_row = 0;
	readline->prompt_col = 0;
	readline->cursor_row = 0;
	readline->cursor_col = 0;
	readline->term_row = 0;
	readline->term_col = 0;
	if (!readline->history || !readline->term)
		return ;
}

void	free_readline(t_rl *readline)
{
	if (readline->history)
	{
		free_history(readline->history);
		free(readline->history);
		readline->history = NULL;
	}
	if (readline->term)
	{
		free(readline->term);
		readline->term = NULL;
	}
	if (readline->prompt)
	{
		free(readline->prompt);
		readline->prompt = NULL;
	}
}

void	handle_clear(int *buffer_pos, char *buffer, t_rl *readline)
{
	add_to_history(buffer, readline->history);
	disable_raw_mode(readline->term);
	write(STDOUT_FILENO, "\033[H\033[J", 6);
	enable_raw_mode(readline->term);
	*buffer_pos = 0;
}

void	handle_arrow_keys(char **buffer, int *buffer_pos, int *capacity, t_rl *readline)
{
	char	c;
	int		len;

	if (read(STDIN_FILENO, &c, 1) != 1 || c != '[')
		return;
	if (read(STDIN_FILENO, &c, 1) != 1)
		return;
	if (!*buffer)
		return;
	len = ft_strlen(*buffer);

	if (c == ARROW_UP || c == ARROW_DOWN)
	{
		handle_history(buffer, buffer_pos, capacity, readline, c);
		return;
	}
	handle_arrow_movement(buffer, buffer_pos, len, c);
}

int	handle_input(char c, char **buffer, int *buffer_pos, int *capacity, t_rl *readline)
{
	int	len;

	if (!*buffer)
		return (0);
	len = ft_strlen(*buffer);
	if (c == BACKSPACE && *buffer_pos > 0)
	{
		handle_backspace(buffer, buffer_pos, len, readline);
		return (1);
	}
	if (c == DELETE)
	{
		handle_delete(buffer, buffer_pos, len);
		return (1);
	}
	if (c >= 32 && c <= 126)
	{
		handle_character(c, buffer, buffer_pos, capacity, len);
		return (1);
	}
	return (0);
}
