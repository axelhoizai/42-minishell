/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline_cursor.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalicem <kalicem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 13:04:34 by mdemare           #+#    #+#             */
/*   Updated: 2025/02/13 03:34:04 by kalicem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	move_cursor(int row, int col)
{
	if (row <= 0 || col <= 0)
		return;
	printf("\033[%d;%dH", row, col);
	fflush(stdout);
}

void	get_prompt_position(t_rl *rl)
{
	char	buf[32];
	int		i;

	i = 0;
	ft_bzero(buf, sizeof(buf));
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
	rl->prompt_row = 0;
	i = 2;
	while (buf[i] >= '0' && buf[i] <= '9')
		rl->prompt_row = rl->prompt_row * 10 + (buf[i++] - '0');
	i++;
	rl->prompt_col = rl->prompt_col * 10 + (buf[i++] - '0');
}

// void	get_prompt_position(t_rl *rl)
// {
// 	char	buf[32];
// 	int		i;

// 	if (!rl)
// 		return;
// 	ft_bzero(buf, sizeof(buf));
// 	write(STDOUT_FILENO, "\033[6n", 4);
// 	i = 0;
// 	while (i < (int)sizeof(buf) - 1)
// 	{
// 		if (read(STDIN_FILENO, buf + i, 1) != 1)
// 			return;
// 		if (buf[i] == 'R')
// 			break;
// 		i++;
// 	}
// 	buf[i] = '\0';
// 	if (buf[0] != '\033' || buf[1] != '[')
// 		return;
// 	rl->prompt_row = 0;
// 	i = 2;
// 	while (buf[i] && buf[i] >= '0' && buf[i] <= '9')
// 		rl->prompt_row = rl->prompt_row * 10 + (buf[i++] - '0');

// 	if (!buf[i] || buf[i] != ';')
// 		return;
// 	i++;
// 	rl->prompt_col = 0;
// 	while (buf[i] && buf[i] >= '0' && buf[i] <= '9')
// 		rl->prompt_col = rl->prompt_col * 10 + (buf[i++] - '0');
// }


void	recalculate_cursor_line_pos(t_rl *rl)
{
	int	relative_row;
	int	absolute_col;

	relative_row = 0;
	absolute_col = 0;
	if (!rl || !rl->term)
		return;
	relative_row = rl->term->cursor_row - rl->prompt_row;
	absolute_col = rl->term->cursor_col;
	rl->cursor_pos = (relative_row * rl->term->term_col) + absolute_col - (rl->prompt_len - 1);
	if (rl->cursor_pos < 0)
		rl->cursor_pos = 0;
	if (rl->cursor_pos > rl->line_length)
		rl->cursor_pos = rl->line_length;
}

int	get_cursor_position(t_rl *rl)
{
	char	buf[32];
	int		i;
	int		ret;
	int		row;
	int		col;

	if (!rl || !rl->term)
		return (-1);
	// write(STDOUT_FILENO, "\033[6n", 4);
	printf("\033[6n");
	fflush(stdout);
	ret = read(STDIN_FILENO, buf, sizeof(buf) - 1);
	if (ret <= 0)
		return (-1);
	buf[ret] = '\0';
	if (buf[0] != '\033' || buf[1] != '[')
		return (-1);
	row = 0;
	i = 2;
	while (buf[i] >= '0' && buf[i] <= '9')
		row = (row * 10) + (buf[i++] - '0');
	i++;
	col = 0;
	while (buf[i] >= '0' && buf[i] <= '9')
		col = (col * 10) + (buf[i++] - '0');
	rl->term->cursor_row = row;
	rl->term->cursor_col = col;
	recalculate_cursor_line_pos(rl);
	return (0);
}
