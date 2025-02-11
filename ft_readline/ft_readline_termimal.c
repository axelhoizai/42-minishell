/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline_termimal.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdemare <mdemare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 14:47:48 by mdemare           #+#    #+#             */
/*   Updated: 2025/02/11 16:44:23 by mdemare          ###   ########.fr       */
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
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &rl->term->original_term);
}
