/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_terminal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdemare <mdemare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 15:15:29 by mdemare           #+#    #+#             */
/*   Updated: 2025/02/14 19:15:17 by mdemare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	reset_terminal(void)
{
	struct termios	term;

	if (tcgetattr(STDIN_FILENO, &term) == -1)
	{
		perror("tcgetattr");
		exit(EXIT_FAILURE);
	}
	term.c_lflag |= (ICANON | ECHO);
	term.c_iflag |= (ICRNL);
	term.c_oflag |= OPOST;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &term) == -1)
		exit(EXIT_FAILURE);
}

void	unconfigure_terminal(void)
{
	t_data	*data;

	data = get_data(NULL);
	data->is_reading = false;
}

void	configure_terminal(void)
{
	t_data	*data;

	data = get_data(NULL);
	data->is_reading = true;
}
