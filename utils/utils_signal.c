/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_signal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdemare <mdemare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 15:19:22 by mdemare           #+#    #+#             */
/*   Updated: 2025/02/14 19:18:18 by mdemare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// Interrompt un programme (CTRL+C)
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
		return;
	printf("\nQuit (core dumped)\n");
	data->exit_code = 131;
	configure_terminal();
	kill(get_pid(), SIGQUIT);
}

// Demande d'arrêt propre (kill <PID>)
static void	handle_sigterm(int sig)
{
	(void)sig;
	exit(0);
}

// Empêche le programme d'être stoppé (CTRL+Z)
static void	handle_sigtstp(int sig)
{
	(void)sig;
}

void handle_sigpipe(int sig)
{
	(void)sig;
	write(STDERR_FILENO, "Broken pipe\n", 12);
}

void handle_sigsegv(int sig)
{
	(void)sig;
	write(STDERR_FILENO, "Segmentation fault detected\n", 28);
	exit(139);
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

	// Gestion de SIGPIPE (Eviter les crashs sur pipe casse)
	sa.sa_handler = handle_sigpipe;
	sigaction(SIGPIPE, &sa, NULL);

	// Gestion de SIGSEGV (Detection des Segmentation Faults)
	sa.sa_handler = handle_sigsegv;
	sigaction(SIGSEGV, &sa, NULL);
}
