/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoizai <ahoizai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 10:50:45 by mdemare           #+#    #+#             */
/*   Updated: 2025/01/30 18:15:48 by ahoizai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	here_doc(t_pipeline *pip, int *p_fd, t_data *data)
{
	char	*next_line;
	(void)data;
	while (1)
	{
		ft_putstr_fd("here_doc> ", STDOUT_FILENO);
		next_line = get_next_line(STDIN_FILENO);
		if (!next_line)
			break ;
		if (ft_strlen(next_line) == (ft_strlen(pip->commands[0]->limiter) + 1)
			&& ft_strncmp(next_line, pip->commands[0]->limiter,
						ft_strlen(pip->commands[0]->limiter)) == 0)
		{
			free(next_line);
			break ;
		}
		ft_putstr_fd(next_line, p_fd[1]);
		free(next_line);
	}
}
