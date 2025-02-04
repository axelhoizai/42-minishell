/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline_input.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdemare <mdemare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 11:03:47 by mdemare           #+#    #+#             */
/*   Updated: 2025/02/04 10:16:39 by mdemare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_backspace(char **buffer, int *buffer_pos, int len, t_rl *readline)
{
	int	i;
	int	term_size;

	get_cursor_position(readline);
	term_size = get_terminal_size(readline);
	if (readline->cursor_row == readline->prompt_row 
		&& readline->cursor_col <= get_prompt_length(readline->prompt))
		return ;
	if (readline->cursor_row > readline->prompt_row && readline->cursor_col == 1)
	{
		printf("\033[%d;%dH\033[J", readline->cursor_row - 1, term_size);
		fflush(stdout);
	}
	(*buffer_pos)--;
	i = *buffer_pos;
	while (i < len - 1)
	{
		(*buffer)[i] = (*buffer)[i + 1];
		i++;
	}
	(*buffer)[len - 1] = '\0';
	write(STDOUT_FILENO, "\b", 1);
	write(STDOUT_FILENO, &(*buffer)[*buffer_pos], len - *buffer_pos);
	write(STDOUT_FILENO, " ", 1);
	while (--len >= *buffer_pos)
		write(STDOUT_FILENO, "\b", 1);
}

void	handle_delete(char **buffer, int *buffer_pos, int len)
{
	int	i;

	if (*buffer_pos < len)
	{
		i = *buffer_pos;
		while (i < len - 1)
		{
			(*buffer)[i] = (*buffer)[i + 1];
			i++;
		}
		(*buffer)[len - 1] = '\0';
		write(STDOUT_FILENO, &(*buffer)[*buffer_pos], len - *buffer_pos);
		write(STDOUT_FILENO, " ", 1);
		while (--len >= *buffer_pos)
			write(STDOUT_FILENO, "\b", 1);
	}
}

void	handle_character(char c, char **buffer, int *buffer_pos, int *capacity, int len)
{
	int	i;

	if (*buffer_pos >= *capacity - 2)
		*buffer = expand_buffer(*buffer, capacity);
	i = len;
	while (i >= *buffer_pos)
		(*buffer)[i + 1] = (*buffer)[i], i--;
	(*buffer)[*buffer_pos] = c;
	write(STDOUT_FILENO, &(*buffer)[*buffer_pos], len - *buffer_pos + 1);
	(*buffer_pos)++;
	while (len-- > *buffer_pos)
		write(STDOUT_FILENO, "\b", 1);
}

int	handle_enter(char *buffer, int buffer_pos, t_rl *readline)
{
	buffer[buffer_pos] = '\0';
	if (buffer_pos == 0)
	{
		write(STDOUT_FILENO, "\n", 1);
		write(STDOUT_FILENO, readline->prompt, readline->prompt_len);
		get_prompt_position(readline);
		return (1);
	}
	if (ft_strcmp(buffer, "clear") == 0)
	{
		handle_clear(&buffer_pos, buffer, readline);
		write(STDOUT_FILENO, readline->prompt, readline->prompt_len);
		get_prompt_position(readline);
		return (1);
	}
	else
	{
		add_to_history(buffer, readline->history);
		write(STDOUT_FILENO, "\n", 1);
		get_prompt_position(readline);
		return (2);
	}
}

int	handle_ctrl_d(int buffer_pos, char *buffer, t_rl *readline)
{
	(void)buffer_pos;
	free(buffer);
	(void)readline;
	write(STDOUT_FILENO, "\n", 1);
	// write(STDOUT_FILENO, readline->prompt, ft_strlen(readline->prompt));
	return (1);
}