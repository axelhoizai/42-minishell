
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

void here_doc(char **limiters, int *p_fd)
{
	char	*next_line;
	int		j;
	int		limiter_count;
	int		matched;

	limiter_count = 0;
	while (limiters[limiter_count])
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
				break;
			if (ft_strlen(next_line) == ft_strlen(limiters[j]) + 1 &&
				ft_strncmp(next_line, limiters[j], ft_strlen(limiters[j])) == 0)
				matched = 1;
			else
				ft_putstr_fd(next_line, p_fd[1]);
			free(next_line);
		}
		j++;
	}
	close(p_fd[1]);
}
