
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

// void	here_doc(t_pipeline *pip, int *p_fd, t_data *data)
// {
// 	char	*next_line;
// 	(void)data;
// 	while (1)
// 	{
// 		ft_putstr_fd("here_doc> ", STDOUT_FILENO);
// 		next_line = get_next_line(STDIN_FILENO);
// 		if (!next_line)
// 			break ;
// 		if (ft_strlen(next_line) == (ft_strlen(pip->cmds[0]->limiter) + 1)
// 			&& ft_strncmp(next_line, pip->cmds[0]->limiter,
// 						ft_strlen(pip->cmds[0]->limiter)) == 0)
// 		{
// 			free(next_line);
// 			break ;
// 		}
// 		ft_putstr_fd(next_line, p_fd[1]);
// 		free(next_line);
// 	}
// }

// void	here_doc(t_command *cmd, int *p_fd)
// {
// 	char	*next_line;
// 	int		i;

// 	i = 0;
// 	while (cmd->limiters && cmd->limiters[i])
// 	{
// 		while (1)
// 		{
// 			ft_putstr_fd("here_doc> ", STDOUT_FILENO);
// 			next_line = get_next_line(STDIN_FILENO);
// 			if (!next_line)
// 				break ;
// 			if (ft_strlen(next_line) == ft_strlen(&cmd->limiters[i]) + 1 &&
// 				ft_strncmp(next_line, &cmd->limiters[i], ft_strlen(&cmd->limiters[i])) == 0)
// 			{
// 				free(next_line);
// 				break ;
// 			}
// 			ft_putstr_fd(next_line, p_fd[1]);
// 			free(next_line);
// 		}
// 		i++;
// 	}
// 	close(p_fd[1]);
// }

// void	here_doc(char **limiters, int *p_fd)
// {
// 	char	*next_line;
// 	int		i;

// 	i = 0;
// 	while (limiters && limiters[i])
// 	{
// 		while (1)
// 		{
// 			write(STDOUT_FILENO, "here_doc> ", 10);
// 			next_line = get_next_line(STDIN_FILENO);
// 			if (!next_line)
// 				break ;
// 			if (ft_strlen(next_line) == ft_strlen(limiters[i]) + 1 &&
// 				ft_strncmp(next_line, limiters[i], ft_strlen(limiters[i])) == 0)
// 			{
// 				free(next_line);
// 				break ;
// 			}
// 			write(p_fd[1], next_line, ft_strlen(next_line));
// 			free(next_line);
// 		}
// 		i++;
// 	}
// 	close(p_fd[1]);
// }

// void	here_doc(char *limiter, int *p_fd)
// {
// 	char	*next_line;

// 	// close(p_fd[0]);
// 	while (1)
// 	{
// 		ft_putstr_fd("here_doc> ", STDOUT_FILENO);
// 		next_line = get_next_line(STDIN_FILENO);
// 		if (!next_line)
// 			break ;
// 		if (ft_strlen(next_line) == ft_strlen(limiter) + 1 &&
// 			ft_strncmp(next_line, limiter, ft_strlen(limiter)) == 0)
// 		{
// 			free(next_line);
// 			break ;
// 		}
// 		ft_putstr_fd(next_line, p_fd[1]);
// 		free(next_line);
// 	}
// 	// close(p_fd[1]);
// 	// exit(0);
// }

// void	here_doc(char *limiter, int *p_fd)
// {
// 	char	*next_line;

// 	close(p_fd[0]);
// 	while (1)
// 	{
// 		write(1, "here_doc> ", 10);
// 		next_line = get_next_line(STDIN_FILENO);
// 		if (!next_line)
// 			break ;
// 		if (ft_strlen(next_line) == ft_strlen(limiter) + 1 &&
// 			ft_strncmp(next_line, limiter, ft_strlen(limiter)) == 0)
// 		{
// 			free(next_line);
// 			break ;
// 		}
// 		write(p_fd[1], next_line, ft_strlen(next_line));
// 		free(next_line);
// 	}
// 	close(p_fd[1]);
// 	exit(0);
// }

void	here_doc(char *limiter, int *p_fd)
{
	char	*next_line;

	while (1)
	{
		write(1, "here_doc> ", 10);
		next_line = get_next_line(STDIN_FILENO);
		if (!next_line)
			break ;
		if (ft_strlen(next_line) == ft_strlen(limiter) + 1 &&
			ft_strncmp(next_line, limiter, ft_strlen(limiter)) == 0)
		{
			free(next_line);
			break ;
		}
		// write(p_fd[1], "next_line = ", 12);
		// write(p_fd[1], next_line, ft_strlen(next_line));
		// write(p_fd[1], ", limiter = ", 12);
		// write(p_fd[1], limiter, ft_strlen(limiter));
		// write(p_fd[1], " ft_strlen(next_line) = ", 24);
		// ft_putnbr_fd(ft_strlen(next_line),  p_fd[1]);
		// write(p_fd[1], " ft_strlen(limiter) = ", 23);
		// ft_putnbr_fd(ft_strlen(limiter), p_fd[1]);
		// write(p_fd[1], "\n", 1);

		
		write(p_fd[1], next_line, ft_strlen(next_line));
		free(next_line);
	}
	// close(p_fd[1]);
}
