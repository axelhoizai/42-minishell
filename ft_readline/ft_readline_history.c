/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline_history.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdemare <mdemare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 21:35:26 by mdemare           #+#    #+#             */
/*   Updated: 2025/02/01 16:04:46 by mdemare          ###   ########.fr       */
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
	int	fd;

	if (!history->history_tab || !cmd || *cmd == '\0')
		return ;
	if (history->history_count < MAX_HISTORY)
	{
		history->history_tab[history->history_count] = ft_strdup(cmd);
		(history->history_count)++;
	}
	fd = open(HISTORY_FILE, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (fd != -1)
	{
		write(fd, cmd, ft_strlen(cmd));
		write(fd, "\n", 1);
		close(fd);
	}
}

void load_history(t_history *history)
{
	int		fd;
	char	*line;
	int		i;

	history->history_tab = (char **)malloc(sizeof(char *) * MAX_HISTORY);
	if (!history->history_tab)
		return ;
	history->history_count = 0;

	fd = open(HISTORY_FILE, O_RDONLY);
	if (fd == -1)
		return ;
	i = 0;
	while ((line = get_next_line(fd)) && i < MAX_HISTORY)
	{
		remove_newline(line);
		history->history_tab[i] = ft_strdup(line);
		free(line);
		i++;
	}
	history->history_count = i;
	close(fd);
}

void	free_history(t_history *history)
{
	int	i;

	if (!history->history_tab)
		return ;
	i = 0;
	while (i < history->history_count)
	{
		free(history->history_tab[i]);
		i++;
	}
	free(history->history_tab);
}
