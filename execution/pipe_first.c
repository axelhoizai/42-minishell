/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_first.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoizai <ahoizai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:03:47 by ahoizai           #+#    #+#             */
/*   Updated: 2025/02/17 16:17:18 by ahoizai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	fst_child(t_command *cmd, t_pipeline *pip, int *p_fd, t_data *data)
{
	close(p_fd[0]);
	if (cmd->in_error == 1 || cmd->out_error == 1)
	{
		free_execute(pip, data);
		close(p_fd[1]);
		exit(1);
	}
	else
	{
		if (cmd->fd_in > -1)
			dup2(cmd->fd_in, STDIN_FILENO);
		if (cmd->fd_out > -1)
			dup2(cmd->fd_out, STDOUT_FILENO);
		else if (cmd->in_error == 0)
			dup2(p_fd[1], STDOUT_FILENO);
		close(p_fd[1]);
		close_fds(pip);
		if (is_builtin(cmd->args[0]))
		{
			handle_builtins(cmd, pip, data);
			free_execute(pip, data);
			exit(0);
		}
		execute(cmd->args, pip, data);
	}
}

void	first_pipe(t_command *cmd, t_pipeline *pip, int *p_fd, t_data *data)
{
	pid_t	child;

	if (pipe(p_fd) == -1)
		exit(PIPE_ERROR);
	child = fork();
	if (child == -1)
		exit(FORK_ERROR);
	if (child == 0)
		fst_child(cmd, pip, p_fd, data);
	close(p_fd[1]);
	if (cmd->fd_in >= 0)
		close(cmd->fd_in);
	if (cmd->fd_in == -2)
		cmd->fd_in = p_fd[0];
	if (pip->cmds[1]->fd_in == -2)
		pip->cmds[1]->fd_in = p_fd[0];
	else
		close(p_fd[0]);
}
