/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline_signal.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdemare <mdemare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 00:33:12 by mdemare           #+#    #+#             */
/*   Updated: 2025/02/04 10:06:32 by mdemare          ###   ########.fr       */
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

void	handle_sigint(int sig)
{
	(void)sig;
	signal(SIGQUIT, SIG_IGN);
	write(STDOUT_FILENO, "^C\n", 3);
	ft_readline_redisplay();
}

#define SIZE_FIX 512

void	ft_readline_redisplay(void)
{
	t_data		*data;
	t_data_term	*term;
	t_rl 		*readline;
	char		*prompt;

	data = get_data(NULL);
	if (!data)
		return ;
	term = get_term_data(NULL);
	if (!term)
		return ;
	readline = get_rl(NULL);
	if (!readline)
		return ;
	readline->buffer_pos = 0;
	ft_bzero(readline->buffer, SIZE_FIX);
	// data->term = term;
	prompt = get_prompt(data->env_ms);
	if (!prompt)
		return;
	write(STDOUT_FILENO, "\r\033[K", 4);
	write(STDOUT_FILENO, prompt, ft_strlen(prompt));
	free(prompt);
}
