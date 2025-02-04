/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline_cursor.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdemare <mdemare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 09:55:52 by mdemare           #+#    #+#             */
/*   Updated: 2025/02/04 10:04:48 by mdemare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	get_prompt_position(t_rl *readline)
{
	char	buf[32];
	int		i;

	i = 0;
	write(STDOUT_FILENO, "\033[6n", 4);
	while (i < (int)sizeof(buf) - 1)
	{
		if (read(STDIN_FILENO, buf + i, 1) != 1)
			break;
		if (buf[i] == 'R')
			break;
		i++;
	}
	buf[i] = '\0';
	readline->prompt_row = 0;
	// readline->prompt_col = 0;
	i = 2;
	while (buf[i] >= '0' && buf[i] <= '9')
		readline->prompt_row = readline->prompt_row * 10 + (buf[i++] - '0');
	i++;
	// 	readline->prompt_col = readline->prompt_col * 10 + (buf[i++] - '0');
}

void	get_cursor_position(t_rl *readline)
{
	char	buf[32];
	int		i;

	i = 0;
	write(STDOUT_FILENO, "\033[6n", 4);
	while (i < (int)sizeof(buf) - 1)
	{
		if (read(STDIN_FILENO, buf + i, 1) != 1)
			break;
		if (buf[i] == 'R')
			break;
		i++;
	}
	buf[i] = '\0';
	readline->cursor_row = 0;
	readline->cursor_col = 0;
	i = 2;
	while (buf[i] >= '0' && buf[i] <= '9')
		readline->cursor_row = readline->cursor_row * 10 + (buf[i++] - '0');
	i++;
	while (buf[i] >= '0' && buf[i] <= '9')
		readline->cursor_col = readline->cursor_col * 10 + (buf[i++] - '0');
}

void	move_cursor(int row, int col)
{
	printf("\033[%d;%dH\033[J", row, col);
	fflush(stdout);
}

int	get_terminal_size(t_rl *readline)
{
	struct winsize	ws;

	if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1)
		return (0);
	readline->term_row = ws.ws_row;
	readline->term_col = ws.ws_col;
	return (ws.ws_col);
}
