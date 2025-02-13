/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline_signal.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdemare <mdemare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 15:19:22 by mdemare           #+#    #+#             */
/*   Updated: 2025/02/13 15:50:53 by mdemare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

// Interrompt un programme (CTRL+C)
static void	handle_sigint(int sig)
{
	t_rl	*rl;

	(void)sig;
	rl = get_rl(NULL);
	write(STDOUT_FILENO, "^C\n", 4);
	rl->buffer_size = 0;
	rl->cursor_pos = 0;
	rl->line_length = 0;
	get_cursor_position(rl);
	get_prompt_position(rl);
	get_terminal_size(rl);
	move_cursor(rl->prompt_row + 1, 0);
	write(STDOUT_FILENO, "\033[K", 3);
	printf("%s", rl->prompt);
	fflush(stdout);
}

int	get_pid(void)
{
	int		fd;
	char	buffer[32];
	int		pid;

	fd = open("/proc/self/stat", O_RDONLY);
	if (fd < 0)
		return (-1);
	if (read(fd, buffer, 31) <= 0)
	{
		close(fd);
		return (-1);
	}
	buffer[31] = '\0';
	pid = ft_atoi(buffer);
	close(fd);
	return (pid);
}

// Quitte le programme (CTRL+\), ignore en mode readline
static void	handle_sigquit(int sig)
{
	t_rl	*rl;
	t_data	*data;

	data = get_data(NULL);
	(void)sig;
	rl = get_rl(NULL);
	if (rl->is_reading)
	{
		// write(STDOUT_FILENO, "\nSIGQUIT ignoré\n", 17);
		return;
	}
	write(STDOUT_FILENO, "\nQuit (core dumped)\n", 20);
	data->exit_code = 131;
	ctrl_d_free(rl);
	configure_terminal();
	kill(get_pid(), SIGQUIT);
	exit(131); // Code de sortie pour SIGQUIT
}

// Demande d'arrêt propre (kill <PID>)
static void	handle_sigterm(int sig)
{
	t_rl	*rl;

	(void)sig;
	rl = get_rl(NULL);
	// write(STDOUT_FILENO, "\nSIGTERM reçu, fermeture propre...\n", 35);
	// debug_log("Fermeture propre\n");
	ctrl_d_free(rl);

	// Ajoute ici du code pour libérer la mémoire et quitter proprement
	_exit(0);
}

// Empêche le programme d'être stoppé (CTRL+Z)
static void	handle_sigtstp(int sig)
{
	(void)sig;
	// write(STDOUT_FILENO, "\nSIGTSTP (CTRL+Z) ignoré\n", 25);
}

// Redimensionnement du terminal
static void	handle_sigwinch(int sig)
{
	t_rl	*rl;

	(void)sig;
	rl = get_rl(NULL);
	get_cursor_position(rl);
	get_terminal_size(rl);
}

void	setup_signal_handlers(void)
{
	struct sigaction sa;

	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);

	// Gestion de CTRL+C (SIGINT)
	sa.sa_handler = handle_sigint;
	sigaction(SIGINT, &sa, NULL);

	// Gestion de CTRL+\ (SIGQUIT)
	sa.sa_handler = handle_sigquit;
	sigaction(SIGQUIT, &sa, NULL);

	// Gestion de SIGTERM (kill <PID>)
	sa.sa_handler = handle_sigterm;
	sigaction(SIGTERM, &sa, NULL);

	// Gestion de SIGTSTP (CTRL+Z) - Ignore
	sa.sa_handler = handle_sigtstp;
	sigaction(SIGTSTP, &sa, NULL);

	// Gestion de SIGWINCH (Redimensionnement du terminal)
	sa.sa_handler = handle_sigwinch;
	sigaction(SIGWINCH, &sa, NULL);
}
