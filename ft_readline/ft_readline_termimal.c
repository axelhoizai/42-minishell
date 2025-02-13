/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline_termimal.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalicem <kalicem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 14:47:48 by mdemare           #+#    #+#             */
/*   Updated: 2025/02/12 23:23:58 by kalicem          ###   ########.fr       */
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

// void	enable_raw_mode()
// {
// 	struct termios	raw;
// 	t_rl			*rl;
	
// 	rl = get_rl(NULL);
// 	tcgetattr(STDIN_FILENO, &rl->term->original_term);
// 	raw = rl->term->original_term;
// 	raw.c_lflag &= ~(ECHO | ICANON | ECHONL);
// 	tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
// 	rl->term->original_term.c_cc[VMIN] = 0;
// 	rl->term->original_term.c_cc[VTIME] = 1;
// }

// void	disable_raw_mode()
// {
// 	t_rl			*rl;
	
// 	rl = get_rl(NULL);
// 	reset_terminal();
// 	tcsetattr(STDIN_FILENO, TCSAFLUSH, &rl->term->original_term);
// }

void	configure_terminal()
{
	struct termios	raw;
	t_rl			*rl;
	
	rl = get_rl(NULL);
	tcgetattr(STDIN_FILENO, &rl->term->original_term);
	raw = rl->term->original_term;
	raw.c_lflag &= ~(ECHO | ICANON | ECHONL);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
	rl->term->original_term.c_cc[VMIN] = 0;
	rl->term->original_term.c_cc[VTIME] = 1;
	rl->is_reading = true;
}

// void	configure_terminal()
// {
// 	t_rl			*rl;
	
// 	rl = get_rl(NULL);
// 	if (tcgetattr(0, &rl->term->original_term) < 0)
// 		return ;
// 	rl->term->original_term.c_lflag &= ~(ECHO | ICANON);
// 	rl->term->original_term.c_cc[VMIN] = 0;
// 	rl->term->original_term.c_cc[VTIME] = 1;
// 	if (tcsetattr(0, 0, &rl->term->original_term) < 0)
// 		return ;
// }

void	unconfigure_terminal()
{
	t_rl			*rl;
	
	rl = get_rl(NULL);
	rl->term->original_term.c_lflag |= (ECHO | ICANON);
	rl->term->original_term.c_cc[VMIN] = 1;
	rl->term->original_term.c_cc[VTIME] = 0;
	rl->is_reading = false;
	reset_terminal();
	if (tcsetattr(0, 0, &rl->term->original_term) < 0)
		return ;
}
