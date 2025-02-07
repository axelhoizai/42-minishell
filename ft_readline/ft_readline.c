/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoizai <ahoizai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 19:24:14 by mdemare           #+#    #+#             */
/*   Updated: 2025/02/07 10:21:19 by ahoizai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//TODO : si input vide et enter, ne pas quitter OK
//TODO : ne pas quitter quand clear OK

//TODO : creer structure pour historique OK
//TODO : si use clear dans historique, doit clear ! OK
//TODO : buffer non limite a 100 / dynamique OK
//TODO : si echo -n, doit ecrire avant le prompt OK (fflush)
//TODO : ne pas pouvoir effacer le prompt (uniquement historique ou long press?) OK?
//TODO : implementer fleche gauche et droite OK?
//TODO : creer structure pour prompt ou fonction OK?
//TODO : trouver pourquoi terminal bug si use historique et ctrl+c ou ctrl+v. Reste raw? je pense : i != 0 OK?
//TODO : si line en haut du terminal ctrl+d ne fonctionne pas (i != 0 ?) OK?

//TODO : ajouter suppr surveiller que les bon caracteres se supprime
//TODO : remplacer SIZE_FIX dans readline_utils
//TODO : maj position prompt quand ctrl+c
//TODO : si prompt remonte car nouvelle ligne en bas du terminla, recalculer sa position
//TODO : monter le curso si fleche gauche au bord du terminal et sous le prompt
//TODO : descendre si fleche du bas et au bord droite du terminal et pas au bout de la chaine de car
//TODO : free readline quand handle exit
//TODO : rendre independant
//TODO : norme
//TODO : faire multi-test pour voir si le terminal
//est reset a chaque fois qu'on quitte le programme
//TODO : faire si historique < 0 ou > historique_len ne rien afficher
//TODO : implementer auto-completion si possible
//TODO : implementer suggestion si possible
//TODO : supprimer ref readline si tout est OK!
// premiere ligne
// second ligne
// 3e ligne

char	*ft_realine_loop(t_rl *readline, char **buffer, int *buffer_pos, int *capacity)
{
	char	c;
	int		res;

	res = 0;
	while (read(STDIN_FILENO, &c, 1) >= 0)
	{
		if (c == CTRLD && handle_ctrl_d(*buffer_pos, *buffer, readline) == 1)
		{
			disable_raw_mode(readline->term);
			return (NULL);
		}
		if (c == ENTER && *buffer_pos > 2)
		{
			// printf ("*buffer_pos = %d\n", *buffer_pos);
			get_prompt_position(readline);
			res = handle_enter(*buffer, *buffer_pos, readline);
			if (res == 2)
				return (*buffer);
		}
		if (c == ESC)
			handle_arrow_keys(buffer, buffer_pos, capacity, readline);
		else if (!handle_input(c, buffer, buffer_pos, capacity, readline))
			get_prompt_position(readline);
	}
	return (NULL);
}

char	*ft_realine(t_rl *readline)
{
	int	capacity;

	fflush(stdout);
	write(STDOUT_FILENO, readline->prompt, ft_strlen(readline->prompt));
	capacity = 64;
	readline->buffer = ft_calloc(capacity, sizeof(char));
	if (!readline->buffer)
		return (NULL);
	readline->buffer_pos = 0;
	readline->history->history_index = readline->history->history_count;
	readline->prompt_len = ft_strlen(readline->prompt);
	enable_raw_mode(readline->term);
	get_rl(readline);
	get_prompt_position(readline);
	readline->buffer = ft_realine_loop(readline, &readline->buffer, &readline->buffer_pos, &capacity);
	disable_raw_mode(readline->term);
	if (readline->buffer_pos == 0)
	{
		free(readline->buffer);
		return (NULL);
	}
	return (readline->buffer);
}
