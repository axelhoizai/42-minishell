/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoizai <ahoizai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 00:37:52 by ahoizai           #+#    #+#             */
/*   Updated: 2025/02/17 19:02:36 by ahoizai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	close_fds(t_pipeline *pip)
{
	int	i;

	i = 0;
	while (pip->cmds[i])
	{
		if (pip->cmds[i]->fd_in > -1)
			close(pip->cmds[i]->fd_in);
		if (pip->cmds[i]->fd_out > -1)
			close(pip->cmds[i]->fd_out);
		i++;
	}
}

static void	last_child(t_command *cmd, t_pipeline *pip, int *p_fd, t_data *data)
{
	close(p_fd[1]);
	if (cmd->in_error == 1 || cmd->out_error == 1)
	{
		free_execute(pip, data);
		close(p_fd[0]);
		exit(1);
	}
	else
	{
		if (cmd->fd_in > -1)
			dup2(cmd->fd_in, STDIN_FILENO);
		else if (pip->cmds[pip->cmd_count - 2]->fd_out < 0)
			dup2(p_fd[0], STDIN_FILENO);
		if (cmd->fd_out > -1)
			dup2(cmd->fd_out, STDOUT_FILENO);
		close(p_fd[0]);
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

static int	last_pipe(t_command *cmd, t_pipeline *pip, int *p_fd, t_data *data)
{
	pip->pid[pip->pipe_cnt - 1] = fork();
	if (pip->pid[pip->pipe_cnt - 1] == -1)
		exit(FORK_ERROR);
	if (pip->pid[pip->pipe_cnt - 1] == 0)
		last_child(cmd, pip, p_fd, data);
	close(p_fd[0]);
	close(p_fd[1]);
	close_fds(pip);
	// waitpid(child, NULL, 0);
	// waitpid(child, &status, 0);
	// if (WIFEXITED(status) && data->exit_code < 128)
	// 	return (WEXITSTATUS(status));
	return (data->exit_code);
}

int	pipex(t_pipeline *pip, t_data *data)
{
	int		p_fd[2];
	int		i;
	int		status;

	i = 0;
	signal(SIGPIPE, SIG_IGN);
	here_doc_init(pip->cmds[i]);
	first_pipe(pip->cmds[0], pip, p_fd, data);
	i++;
	while (i < pip->cmd_count - 1)
	{
		here_doc_init(pip->cmds[i]);
		multi_pipe(pip, p_fd, data, &i);
		i++;
	}
	here_doc_init(pip->cmds[i]);
	status = last_pipe(pip->cmds[i], pip, p_fd, data);
	while (pip->pipe_cnt >= 0)
	{
		waitpid(pip->pid[pip->pipe_cnt], &status, 0);
		pip->pipe_cnt--;
	}
	if (WIFEXITED(status) && data->exit_code < 128)
		return (WEXITSTATUS(status));
	return (data->exit_code);
}
