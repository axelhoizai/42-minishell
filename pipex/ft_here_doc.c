
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdemare <mdemare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 10:50:45 by mdemare           #+#    #+#             */
/*   Updated: 2025/02/11 09:43:27 by mdemare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void here_doc(t_command *cmd)
{
	char	*next_line;
	int		j;
	int		limiter_count;
	int		matched;

	limiter_count = 0;
	if (cmd->heredoc == 1)
	{
		if (cmd->fd_in > -1)
			close(cmd->fd_in);
		cmd->fd_in = open("here_doc", O_RDWR | O_CREAT, 0777);
	}
	print_tab(cmd->limiters);
	while (cmd->limiters[limiter_count])
		limiter_count++;
	j = 0;
	while (j < limiter_count)
	{
		matched = 0;
		while (!matched)
		{
			ft_putstr_fd("here_doc> ", STDOUT_FILENO);
			next_line = get_next_line(STDIN_FILENO);
			if (!next_line)
			{
				// free_tab(cmd->limiters);
				break;
			}
			if (ft_strlen(next_line) == ft_strlen(cmd->limiters[j]) + 1 &&
				ft_strncmp(next_line, cmd->limiters[j], ft_strlen(cmd->limiters[j])) == 0)
				matched = 1;
			else
			{
				if (j == limiter_count - 1 && cmd->heredoc == 1)
					ft_putstr_fd(next_line, cmd->fd_in);
			}
			free(next_line);
		}
		j++;
	}
	if (cmd->heredoc == 1)
	{
		close(cmd->fd_in);
		cmd->fd_in = open("here_doc", O_RDONLY);
		unlink("here_doc");
	}
	// printf("cmd->fd_in here_doc last : %d\n", cmd->fd_in);
}
