/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdemare <mdemare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 15:16:28 by mdemare           #+#    #+#             */
/*   Updated: 2025/02/11 16:50:52 by mdemare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
//TODO : BUFFER NON RESET APRES ENTRE!!!!!!!!! ok?

//TODO : permettre le echo -n

//TODO : Tester problème d'affichage, surtout arrow left and right et position cursor and prompt
//TODO : Probleme de copier coller, lignes suivantes decale
//TODO : quand move et ecrit, ecris et descend ligne du dessous, multi lignes?
//TODO : remettre historique
//TODO : revoir les signaux
// - SIGINT (CTRL+C) : Interrompt la saisie et reaffiche le prompt proprement
// - SIGQUIT (CTRL+\) : Ignore pour eviter la fermeture brutale du shell
// - SIGTSTP (CTRL+Z) : Desactive ou gere pour empecher la suspension du shell
// - SIGWINCH : Detecte un changement de taille du terminal et met a jour l'affichage
// - SIGTERM : Peut etre capture pour une sortie propre si necessaire
//TODO : remplacer malloc en ft_safe_malloc
//TODO : tester l'effacement multilignes 
//TODO : ajout BUFFER static

// void	replace_char_at_cursor(t_rl *rl, char c)
// {
// 	if (!rl || !rl->buffer || rl->cursor_pos >= rl->buffer_size - 1)
// 		return;
// 	rl->buffer[rl->cursor_pos] = c;
// 	if (rl->cursor_pos == rl->line_length)
// 		rl->line_length++;
// 	write(STDOUT_FILENO, &c, 1);
// 	rl->cursor_pos++;
// }

// void update_prompt_position(t_rl *rl)
// {
// 	int previous_prompt_row;
// 	int diff;

// 	diff = 0;
// 	if (!rl)
// 		return;
// 	previous_prompt_row = rl->prompt_row;
// 	get_cursor_position(rl);
// 	if (rl->prompt_row > previous_prompt_row)
// 	{
// 		diff = rl->prompt_row - previous_prompt_row;
// 		rl->prompt_row -= diff;
// 	}
// }

void	ctrl_d_free(t_rl *rl)
{
	t_data *data;

	data = get_data(NULL);
	free_history(rl);
	free_var(rl->buffer);
	free_var(rl->prompt);
	free_readline(rl);
	handle_exit(NULL, data);
}

void	process_input(t_rl *rl, char c, int *bytes_available)
{
	if (c == BACKSPACE)
		handle_backspace(rl);
	else if (c == ESC)
		handle_arrow_keys(rl, c);
	else if (c == CTRL_D)
	{
		// write(STDOUT_FILENO, "exit\nTape \'stty sane\' si teminal bug\n", 38);
		printf("exit\n");

		disable_raw_mode();
		ctrl_d_free(rl);
		*bytes_available = -1;
		exit(0);
	}
	else if (ft_isprint(c))
		insert_char_at_cursor(rl, c);
	fflush(stdout);
}

void	ft_realine_loop(t_rl *rl)
{
	char	c;
	int		bytes_available;

	bytes_available = 0;
	while (1)
	{
		ioctl(STDIN_FILENO, FIONREAD, &bytes_available);
		if (read(STDIN_FILENO, &c, 1) >= 0)
		{
			if (c == ENTER)
			{
				if (handle_enter(rl, bytes_available, c) == 1)
					break ;
				update_display(rl);
			}
			else
				process_input(rl, c, &bytes_available);
		}
	}
}

// char *ft_readline(t_rl *rl)
// {
// 	// init_readline(rl);
// 	get_rl(rl);
// 	enable_raw_mode();

// 	rl->history->history_index = rl->history->history_count;
// 	rl->prompt_len = actual_prompt_length(rl->prompt);
// 	write(STDOUT_FILENO, rl->prompt, ft_strlen(rl->prompt));
// 	get_prompt_position(rl);
// 	get_cursor_position(rl);
// 	get_terminal_size(rl);
// 	fflush(stdout);
// 	ft_realine_loop(rl);
// 	disable_raw_mode();
// 	free_var(rl->prompt);
// 	return (rl->buffer);
// }

char *ft_readline(t_rl *rl)
{
	char	*buffer_copy;

	get_rl(rl);
	enable_raw_mode();
	rl->history->history_index = rl->history->history_count;
	rl->prompt_len = actual_prompt_length(rl->prompt);
	write(STDOUT_FILENO, rl->prompt, ft_strlen(rl->prompt));
	get_prompt_position(rl);
	get_cursor_position(rl);
	get_terminal_size(rl);
	fflush(stdout);
	ft_realine_loop(rl);
	// disable_raw_mode();
	free_var(rl->prompt);
	buffer_copy = ft_strdup(rl->buffer);
	if (!buffer_copy)
		return (NULL);
	ft_bzero(rl->buffer, rl->buffer_size);
	rl->line_length = 0;
	rl->cursor_pos = 0;
	return (buffer_copy);
}

//premiere ligne
//second ligne
//3e ligne

//une ligne long qui depasse le terminal