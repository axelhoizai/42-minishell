/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline_history.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdemare <mdemare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 21:35:26 by mdemare           #+#    #+#             */
/*   Updated: 2025/02/10 19:30:57 by mdemare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	remove_newline(char *line)
{
	int	len;

	if (!line)
		return ;
	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
}

void	add_to_history(char *cmd, t_history *history)
{
	int		fd;
	char	**new_tab;
	int		new_size;
	int		i;

	if (!cmd || *cmd == '\0')
		return ;
	new_size = history->history_count + 2;
	new_tab = (char **)malloc(sizeof(char *) * new_size);
	if (!new_tab)
		return ;
	i = 0;
	while (i < history->history_count)
	{
		new_tab[i] = history->history_tab[i];
		i++;
	}
	new_tab[i] = ft_strdup(cmd);
	new_tab[i + 1] = NULL;
	free(history->history_tab);
	history->history_tab = new_tab;
	history->history_count++;
	fd = open(HISTORY_FILE, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (fd != -1)
	{
		write(fd, cmd, ft_strlen(cmd));
		write(fd, "\n", 1);
		close(fd);
	}
}

void	load_history(t_history *history)
{
	int		fd;
	char	*line;
	char	**new_tab;
	int		new_size;

	history->history_count = 0;
	history->history_tab = NULL;
	fd = open(HISTORY_FILE, O_RDONLY);
	if (fd == -1)
		return ;
	while ((line = get_next_line(fd)))
	{
		remove_newline(line);
		new_size = history->history_count + 2;
		new_tab = (char **)malloc(sizeof(char *) * new_size);
		if (!new_tab)
		{
			free(line);
			break;
		}
		int j = 0;
		while (j < history->history_count)
		{
			new_tab[j] = history->history_tab[j];
			j++;
		}
		new_tab[j] = ft_strdup(line);
		new_tab[j + 1] = NULL;
		free(history->history_tab);
		history->history_tab = new_tab;

		free(line);
		history->history_count++;
	}
	close(fd);
}

void	free_history(t_rl *rl)
{
	int	i;

	if (!rl || !rl->history)
		return;
	i = 0;
	while (i < rl->history->history_count)
	{
		free(rl->history->history_tab[i]);
		i++;
	}
	free(rl->history->history_tab);
	rl->history->history_tab = NULL;
	free(rl->history);
	rl->history = NULL;
}

