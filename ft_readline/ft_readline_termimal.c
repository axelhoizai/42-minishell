/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline_termimal.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoizai <ahoizai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 14:47:48 by mdemare           #+#    #+#             */
/*   Updated: 2025/02/12 14:43:58 by ahoizai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	get_terminal_size(t_rl *rl)
{
	struct winsize	ws;

	rl->term->term_row = 80;
	rl->term->term_col = 0;
	
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws);
	rl->term->term_row = ws.ws_row; //hauteur
	rl->term->term_col = ws.ws_col; //largeur
}

void	reset_terminal()
{
	struct termios term;

	// Récupérer les paramètres actuels du terminal
	if (tcgetattr(STDIN_FILENO, &term) == -1) {
		perror("tcgetattr");
		exit(EXIT_FAILURE);
	}

	// Rétablir les paramètres du terminal en mode "cooked" (mode normal)
	term.c_lflag |= (ICANON | ECHO);  // Mode canonique, activation de l'écho
	term.c_iflag |= (ICRNL);		  // Conversion CR -> NL
	term.c_oflag |= OPOST;			// Activation des sorties

	// Appliquer les changements au terminal
	if (tcsetattr(STDIN_FILENO, TCSANOW, &term) == -1)
	{
		// perror("tcsetattr");
		exit(EXIT_FAILURE);
	}

	// Optionnel : Vous pouvez aussi restaurer d'autres paramètres si nécessaire.
}

void	enable_raw_mode()
{
	struct termios	raw;
	t_rl			*rl;
	
	rl = get_rl(NULL);
	tcgetattr(STDIN_FILENO, &rl->term->original_term);
	raw = rl->term->original_term;
	// raw.c_lflag &= ~(ECHO | ICANON);
	raw.c_lflag &= ~(ECHO | ICANON | ECHONL);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

void	disable_raw_mode()
{
	t_rl			*rl;
	
	rl = get_rl(NULL);
	reset_terminal();
	// tcsetattr(STDIN_FILENO, TCSAFLUSH, &rl->term->original_term);
}
