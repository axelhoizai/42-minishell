/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdemare <mdemare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 10:50:45 by mdemare           #+#    #+#             */
/*   Updated: 2025/02/17 15:48:25 by mdemare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	here_doc(t_command *cmd, char *next_line, int limiter_cnt, int matched)
{
	int		j;

	j = 0;
	while (j < limiter_cnt)
	{
		matched = 0;
		while (!matched)
		{
			ft_putstr_fd("here_doc> ", STDOUT_FILENO);
			next_line = get_next_line(STDIN_FILENO);
			if (!next_line)
				break ;
			if (ft_strlen(next_line) == ft_strlen(cmd->limiters[j]) + 1
				&& ft_strncmp(next_line, cmd->limiters[j],
					ft_strlen(cmd->limiters[j])) == 0)
				matched = 1;
			else
			{
				if (j == limiter_cnt - 1 && cmd->heredoc == 1)
					ft_putstr_fd(next_line, cmd->fd_in);
			}
			free(next_line);
		}
		j++;
	}
}

void	here_doc_init(t_command *cmd)
{
	char	*next_line;
	int		j;
	int		limiter_count;
	int		matched;

	next_line = NULL;
	j = 0;
	matched = 0;
	limiter_count = 0;
	if (cmd->heredoc == 1)
	{
		if (cmd->fd_in > -1)
			close(cmd->fd_in);
		cmd->fd_in = open("here_doc", O_RDWR | O_CREAT, 0777);
	}
	while (cmd->limiters && cmd->limiters[limiter_count])
		limiter_count++;
	here_doc(cmd, next_line, limiter_count, matched);
	if (cmd->heredoc == 1)
	{
		close(cmd->fd_in);
		cmd->fd_in = open("here_doc", O_RDONLY);
		unlink("here_doc");
	}
}
