/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_signal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoizai <ahoizai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 15:19:22 by mdemare           #+#    #+#             */
/*   Updated: 2025/02/26 10:07:40 by ahoizai          ###   ########.fr       */
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
	data->is_reading = true;
	if (data->is_reading)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

static void	handle_sigquit(int sig)
{
	t_data	*data;

	data = get_data(NULL);
	(void)sig;
	if (data->is_reading)
		return ;
	printf("Quit (core dumped)\n");
	data->exit_code = 131;
	data->is_reading = true;
	kill(get_process_id(), SIGQUIT);
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
}
