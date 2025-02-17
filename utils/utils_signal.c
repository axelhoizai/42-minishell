/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_signal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoizai <ahoizai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 15:19:22 by mdemare           #+#    #+#             */
/*   Updated: 2025/02/17 14:55:42 by ahoizai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	handle_sigint(int sig)
{
	t_data	*data;

	data = get_data(NULL);
	(void)sig;
	printf("^C\n");
	data->exit_code = 130;
	configure_terminal();
	if (data->is_reading)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

// Quitte le programme (CTRL+\), ignore en mode readline
static void	handle_sigquit(int sig)
{
	t_data	*data;

	data = get_data(NULL);
	(void)sig;
	if (data->is_reading)
		return ;
	printf("\nQuit (core dumped)\n");
	data->exit_code = 131;
	configure_terminal();
	kill(get_process_id(), SIGQUIT);
}

void	handle_sigpipe(int sig)
{
	(void)sig;
	write(STDERR_FILENO, "Broken pipe\n", 12);
}

void	handle_sigsegv(int sig)
{
	(void)sig;
	write(STDERR_FILENO, "Segmentation fault detected\n", 28);
	exit(139);
}

void	setup_signal_handlers(void)
{
	struct sigaction	sa;

	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sa.sa_handler = handle_sigint;
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = handle_sigquit;
	sigaction(SIGQUIT, &sa, NULL);
	sa.sa_handler = handle_sigpipe;
	sigaction(SIGPIPE, &sa, NULL);
	sa.sa_handler = handle_sigsegv;
	sigaction(SIGSEGV, &sa, NULL);
}
