/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_terminal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdemare <mdemare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 15:15:29 by mdemare           #+#    #+#             */
/*   Updated: 2025/02/14 15:33:17 by mdemare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	reset_terminal()
{
	struct termios term;

	if (tcgetattr(STDIN_FILENO, &term) == -1) {
		perror("tcgetattr");
		exit(EXIT_FAILURE);
	}
	term.c_lflag |= (ICANON | ECHO);
	term.c_iflag |= (ICRNL);
	term.c_oflag |= OPOST;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &term) == -1)
		exit(EXIT_FAILURE);
}

void	unconfigure_terminal()
{
	t_data			*data;
	
	data = get_data(NULL);
	// data->term->original_term.c_lflag |= (ECHO | ICANON);
	// data->term->original_term.c_cc[VMIN] = 1;
	// data->term->original_term.c_cc[VTIME] = 0;
	data->is_reading = false;
	// reset_terminal();
	// if (tcsetattr(0, 0, &data->term->original_term) < 0)
	// 	return ;
}

void	configure_terminal()
{
	// struct termios	raw;
	t_data			*data;
	
	data = get_data(NULL);
	// tcgetattr(STDIN_FILENO, &data->term->original_term);
	// raw = data->term->original_term;
	// raw.c_lflag &= ~(ECHO | ICANON | ECHONL);
	// tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
	// data->term->original_term.c_cc[VMIN] = 0;
	// data->term->original_term.c_cc[VTIME] = 1;
	data->is_reading = true;
}
