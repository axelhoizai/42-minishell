/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_multi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdemare <mdemare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:19:03 by ahoizai           #+#    #+#             */
/*   Updated: 2025/02/19 10:13:20 by mdemare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	mlt_child(t_command *cmd, t_pipeline *pip, int *p_fd, t_data *data)
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
		else if (cmd->fd_out < 0 && cmd->out_error == 0 && cmd->in_error == 0)
			dup2(p_fd[1], STDOUT_FILENO);
		close(p_fd[1]);
		close_fds(pip);
		if (cmd->args[0] && is_builtin(cmd->args[0]))
		{
			handle_builtins(cmd, pip, data);
			free_execute(pip, data);
			exit(0);
		}
		execute(cmd->args, pip, data);
	}
}

void	multi_pipe(t_pipeline *pip, int *p_fd, t_data *data, int *i)
{
	int	pipe_cmd;

	pipe_cmd = pip->pipe_cnt + 1;
	if (pipe(p_fd) == -1)
		exit(PIPE_ERROR);
	pip->pid[pipe_cmd - *i] = fork();
	if (pip->pid[pipe_cmd - *i] == -1)
		exit(FORK_ERROR);
	if (pip->pid[pipe_cmd - *i] == 0)
		mlt_child(pip->cmds[*i], pip, p_fd, data);
	close(p_fd[1]);
	if (pip->cmds[*i]->fd_in >= 0)
		close(pip->cmds[*i]->fd_in);
	if (pip->cmds[*i]->fd_in == -2)
		pip->cmds[*i]->fd_in = p_fd[0];
	if (pip->cmds[*i + 1]->fd_in == -2)
		pip->cmds[*i + 1]->fd_in = p_fd[0];
	else
		close(p_fd[0]);
}
