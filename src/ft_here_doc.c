/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdemare <mdemare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 10:50:45 by mdemare           #+#    #+#             */
/*   Updated: 2025/01/20 17:41:21 by mdemare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	here_doc(char **argv, int *p_fd)
{
	char	*next_line;

	while (1)
	{
		ft_putstr_fd("here_doc> ", STDOUT_FILENO);
		next_line = get_next_line(STDIN_FILENO);
		if (!next_line)
			break ;
		if (ft_strlen(next_line) == (ft_strlen(argv[2]) + 1)
			&& ft_strncmp(next_line, argv[2], ft_strlen(argv[2])) == 0)
		{
			free(next_line);
			break ;
		}
		ft_putstr_fd(next_line, p_fd[1]);
		free(next_line);
	}
}
