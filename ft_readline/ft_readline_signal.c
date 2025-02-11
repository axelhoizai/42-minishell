/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline_signal.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdemare <mdemare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 15:19:22 by mdemare           #+#    #+#             */
/*   Updated: 2025/02/11 16:46:27 by mdemare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//Interrompt un programme (CTRL+C)
static void	handle_sigint(int sig)
{
	t_rl	*rl;

	(void)sig;
	rl = get_rl(NULL);
	write(STDOUT_FILENO, "^C\n", 5);
	// free(rl->buffer);
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

// Quitte le programme (CTRL+\), ignore
static void	handle_sigquit(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\nSIGQUIT ignoré\n", 17);
}

//Demande d'arret propre
static void	handle_sigterm(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\nSIGTERM reçu, fermeture propre...\n", 35);
	// Ajoute ici du code pour libérer la mémoire et quitter proprement
	_exit(0);
}

//Redimensionnement du terminal
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
	// sa.sa_handler = SIG_IGN; //ignore
	sigaction(SIGINT, &sa, NULL);

	// Gestion de CTRL+\ (SIGQUIT) - Ignore
	sa.sa_handler = handle_sigquit;
	sigaction(SIGQUIT, &sa, NULL);

	// Gestion du redimensionnement (SIGWINCH)
	sa.sa_handler = handle_sigwinch;
	sigaction(SIGWINCH, &sa, NULL);

	// Gerer proprement SIGTERM
	sa.sa_handler = handle_sigterm;
	sigaction(SIGTERM, &sa, NULL);
}
