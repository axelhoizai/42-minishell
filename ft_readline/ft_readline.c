/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdemare <mdemare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 15:16:28 by mdemare           #+#    #+#             */
/*   Updated: 2025/02/13 16:20:26 by mdemare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
//TODO : BUFFER NON RESET APRES ENTRE!!!!!!!!! ok?
//TODO : remettre historique OK ?
//TODO : permettre le echo -n ok ?
//TODO : Probleme de copier coller, lignes suivantes decale OK?
//TODO : revoir les signaux // ok?
// - SIGINT (CTRL+C) : Interrompt la saisie et reaffiche le prompt proprement
// - SIGQUIT (CTRL+\) : Ignore pour eviter la fermeture brutale du shell
// - SIGTSTP (CTRL+Z) : Desactive ou gere pour empecher la suspension du shell
// - SIGWINCH : Detecte un changement de taille du terminal et met a jour l'affichage
// - SIGTERM : Peut etre capture pour une sortie propre si necessaire

//TODO : regrouper les free au même endroits pour eviter les invalides si free aussi dans minishell
//TODO : Tester problème d'affichage, surtout arrow left and right et position cursor and prompt
//TODO : quand move et ecrit, ecris et descend ligne du dessous, multi lignes?
//TODO : remplacer malloc en ft_safe_malloc
//TODO : tester l'effacement multilignes 
//TODO : ajout BUFFER dynamique
//TODO : maj stocker les coordonée du prompt uniquement quand printf prompt, mettre dans une fonction

//TODO : gestion de la conversion entre le buffer 1D et le terminal 2D
// - Les `\n` dans le buffer indiquent des nouvelles lignes à compter,
//	 ajoutées au numéro de ligne du prompt (rl->prompt_col) pour déterminer la ligne réelle dans le terminal
// - Pour retrouver la position dans le buffer depuis le terminal,
//	 il faut additionner les lignes du buffer jusqu'à la ligne cible
// - Dans le buffer, tout ce qui est avant le premier `\n` ou `\0` est sur la même ligne que le prompt
// - Après chaque `\n`, on passe à une nouvelle ligne jusqu'au prochain `\n` ou `\0`
// - La lecture se fait de gauche à droite
// - Chaque `\n` dans le buffer correspond à un retour à la ligne,
//	 et le caractère juste après correspond toujours au bord gauche du terminal
// le buffer vas de 0 à rl->buffer_size et rl->buffer_lines_cnt retourne le nombre de \n
void	ctrl_d_free(t_rl *rl)
{
	t_data *data;

	data = get_data(NULL);
	unconfigure_terminal();
	free_history(rl);
	free_var(rl->buffer);
	free_var(rl->prompt);
	free_readline(rl);
	get_rl(NULL);
	if (data)
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
		// printf("exit\n");
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

char *ft_readline(t_rl *rl)
{
	get_rl(rl);
	configure_terminal();
	rl->history->history_index = rl->history->history_count;
	rl->prompt_len = actual_prompt_length(rl->prompt);
	printf("%s", rl->prompt);
	get_prompt_position(rl);
	get_cursor_position(rl);
	get_terminal_size(rl);
	fflush(stdout);
	ft_realine_loop(rl);
	free_var(rl->prompt);
	// free_var(rl->buffer_copy);
	rl->buffer_copy = ft_strdup(rl->buffer);
	if (!rl->buffer_copy)
		return (NULL);
	ft_bzero(rl->buffer, rl->buffer_size);
	rl->line_length = 0;
	rl->cursor_pos = 0;
	unconfigure_terminal();
	return (rl->buffer_copy);
}
//premiere ligne
//second ligne
//3e ligne

//une ligne long qui depasse le terminal