/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline_arrow.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdemare <mdemare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 10:17:18 by mdemare           #+#    #+#             */
/*   Updated: 2025/02/04 10:18:38 by mdemare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_arrow_movement(char **buffer, int *buffer_pos, int len, char c)
{
	if (c == ARROW_LEFT && *buffer_pos > 0)
	{
		write(STDOUT_FILENO, "\b", 1);
		(*buffer_pos)--;
	}
	else if (c == ARROW_RIGHT && *buffer_pos < len)
	{
		write(STDOUT_FILENO, &(*buffer)[*buffer_pos], 1);
		(*buffer_pos)++;
	}
}

void	handle_history(char **buffer, int *buffer_pos, int *capacity, t_rl *readline, char c)
{
	char	*history_entry;
	int		entry_len;

	if (c == ARROW_UP && readline->history->history_index > 0)
		readline->history->history_index--;
	else if (c == ARROW_DOWN && readline->history->history_index < readline->history->history_count - 1)
		readline->history->history_index++;
	*buffer_pos = 0;
	if (readline->history->history_index >= 0)
		history_entry = readline->history->history_tab[readline->history->history_index];
	if (readline->history->history_index >= 0 && history_entry)
	{
		entry_len = ft_strlen(history_entry);
		if (entry_len + 1 >= *capacity)
		{
			*capacity += entry_len;
			*buffer = expand_buffer(*buffer, capacity);
		}
		print_prompt(readline);
		ft_bzero(*buffer, *capacity);
		ft_strlcpy(*buffer, history_entry, *capacity);
		*buffer_pos = ft_strlen(*buffer);
		write(STDOUT_FILENO, *buffer, *buffer_pos);
		readline->buffer_size = *capacity;
	}
}
