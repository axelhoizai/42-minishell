/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdemare <mdemare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 19:24:14 by mdemare           #+#    #+#             */
/*   Updated: 2025/02/01 18:21:47 by mdemare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//TODO : si input vide et enter, ne pas quitter
//TODO : si echo -n, doit ecrire avant le prompt
//TODO : trouver pour terminal bug si use historique et ctrl+c ou ctrl+v
//TODO : ne pas quitter quand clear
//TODO : creer structure pour historique
//TODO : faire si historique < 0 ou > historique_len ne rien afficher
//TODO : creer structure pour prompt ou fonction
//TODO : buffer non limite a 100 / dynamique
//TODO : implementer fleche gauche et droite
//TODO : norme
//TODO : faire multi-test pour voir si le terminal
//est reset a chaque fois qu'on quitte le programme
//TODO : implementer auto-completion
//TODO : implementer suggestion
void	free_readline(t_rl *readline)
{
		if (readline->history)
	{
		free_history(readline->history);
		free(readline->history);
		readline->history = NULL;
	}
	if (readline->term)
	{
		free(readline->term);
		readline->term = NULL;
	}
	if (readline->prompt)
	{
		free(readline->prompt);
		readline->prompt = NULL;
	}
}

void	init_readline(t_rl *readline)
{
	readline->prompt_len = 0;
	readline->prompt = NULL;
	readline->history = (t_history *)malloc(sizeof(t_history));
	if (!readline->history)
		return ;
	readline->history->history_count = 0;
	readline->history->history_index = 0;
	load_history(readline->history);
	readline->term = (t_data_term *)malloc(sizeof(t_data_term));
	if (!readline->term)
	{
		free_readline(readline);
		return ;
	}
	save_terminal_settings(readline->term);
	setup_signals();
	if (!readline->history || !readline->term)
		return ;
}

static int	handle_ctrl_d(int i, char *buffer, t_rl *readline)
{
	if (i == 0)
	{
		free(buffer);
		write(STDOUT_FILENO, "\n", 1);
		write(STDOUT_FILENO, readline->prompt, ft_strlen(readline->prompt));
		return (1);
	}
	return (0);
}

int	handle_input(char c, char *buffer, int *i, t_rl *readline)
{
	if (c == BACKSPACE && *i >= 0)
	{
		if (*i + readline->prompt_len + 1 > readline->prompt_len + 1)
		{
			(*i)--;
			write(STDOUT_FILENO, "\b \b", 3);
		}
		return (1);
	}
	else if (*i < BUFFER_SIZE - 1)
	{
		buffer[(*i)++] = c;
		write(STDOUT_FILENO, &c, 1);
		return (1);
	}
	return (0);
}
static void	handle_clear(int *i, char *buffer, t_rl *readline)
{
	add_to_history(buffer, readline->history);
	disable_raw_mode(readline->term);
	write(STDOUT_FILENO, "\033[H\033[J", 6);
	enable_raw_mode(readline->term);
	i = 0;
}

void	handle_arrow_keys(char *buffer, int *i, t_rl *readline)
{
	char	c;
	int		j;

	read(STDIN_FILENO, &c, 1);
	if (c == '[')
	{
		read(STDIN_FILENO, &c, 1);
		if (c == ARROW_UP)
		{
			if (readline->history->history_index > 0)
				readline->history->history_index--;
		}
		else if (c == ARROW_DOWN)
		{
			if (readline->history->history_index < readline->history->history_count - 1)
				readline->history->history_index++;
		}
		write(STDOUT_FILENO, "\r", 1);
		write(STDOUT_FILENO, readline->prompt, readline->prompt_len);
		j = *i;
		while (j-- > 0)
			write(STDOUT_FILENO, " ", 1);
		while ((*i)-- > 0)
			write(STDOUT_FILENO, "\b \b", 3);
		if (readline->history->history_index >= 0 && readline->history->history_index < readline->history->history_count
			&& readline->history->history_tab[readline->history->history_index])
		{
			ft_strcpy(buffer, readline->history->history_tab[readline->history->history_index]);
			*i = ft_strlen(buffer);
			write(STDOUT_FILENO, buffer, *i);
		}
		else
			*i = 0;
	}
}

int	handle_enter(char *buffer, int i, t_rl *readline)
{
	buffer[i] = '\0';
	if (ft_strcmp(buffer, "clear") == 0)
	{
		handle_clear(&i, buffer, readline);
		return (1);
	}
	else
	{
		add_to_history(buffer, readline->history);
		write(STDOUT_FILENO, "\n", 1);
		return (2);
	}
}

char	*ft_realine_loop(t_rl *readline, char *buffer, int *i)
{
	char	c;
	int		res;

	res = 0;
	while (read(STDIN_FILENO, &c, 1) > 0)
	{
		if (c == CTRLD && handle_ctrl_d(*i, buffer, readline) == 1)
		{
			disable_raw_mode(readline->term);
			return (NULL);
		}
		else if (c == ENTER)
		{
			res = handle_enter(buffer, *i, readline);
			if (res == 1)
				break;
			else if (res == 2)
				return (buffer);
		}
		else if (c == ESC)
			handle_arrow_keys(buffer, i, readline);
		else if (!handle_input(c, buffer, i, readline))
			continue;
	}
	return (NULL);
}

char	*ft_realine(t_rl *readline)
{
	char	*buffer;
	int		i;

	buffer = (char *)malloc(BUFFER_SIZE);
	if (!buffer)
		return (NULL);
	i = 0;
	readline->history->history_index = readline->history->history_count;
	readline->prompt_len = ft_strlen(readline->prompt);
	enable_raw_mode(readline->term);
	buffer = ft_realine_loop(readline, buffer, &i);
	if (i == 0)
	{
		free(buffer);
		return (NULL);
	}
	return (buffer);
}
