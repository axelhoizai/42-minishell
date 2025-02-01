/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline_signal.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdemare <mdemare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 00:33:12 by mdemare           #+#    #+#             */
/*   Updated: 2025/01/31 15:32:54 by mdemare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	save_terminal_settings(t_data_term *term)
{
	if (tcgetattr(STDIN_FILENO, &term->original_term) == -1)
		write(STDERR_FILENO, "Error: cannot save terminal settings\n", 37);
}

void	restore_terminal_settings(t_data_term *term)
{
	if (tcsetattr(STDIN_FILENO, TCSANOW, &term->original_term) == -1)
		write(STDERR_FILENO, "Error: cannot restore terminal settings\n", 40);
}

void	setup_signals(void)
{
	struct sigaction sa;

	ft_bzero(&sa, sizeof(sa));
	sa.sa_handler = handle_sigint;
	sa.sa_flags = SA_RESTART;
	signal(SIGQUIT, SIG_IGN);
	sigaction(SIGINT, &sa, NULL);
}

// void	setup_signals(void)
// {
// 	struct sigaction sa;


// 	ft_bzero(&sa, sizeof(sa));
// 	sa.sa_handler = handle_sigint;
// 	sa.sa_flags = SA_RESTART;
// 	sigemptyset(&sa.sa_mask);
// 	sigaction(SIGINT, &sa, NULL);
// 	sa.sa_handler = SIG_IGN;
// 	sigaction(SIGQUIT, &sa, NULL);
// }