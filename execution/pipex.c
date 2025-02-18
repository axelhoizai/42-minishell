/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoizai <ahoizai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 00:37:52 by ahoizai           #+#    #+#             */
/*   Updated: 2025/02/18 17:48:39 by ahoizai          ###   ########.fr       */
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
		else if (pip->cmds[pip->pipe_cnt - 1]->fd_out < 0)			
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

void	last_pipe(t_pipeline *pip, int *p_fd, t_data *data, int *i)
{
	int	pipe_cmd;

	pipe_cmd = pip->pipe_cnt + 1;
	pip->pid[pipe_cmd - *i] = fork();
	if (pip->pid[pipe_cmd - *i] == -1)
		exit(FORK_ERROR);
	if (pip->pid[pipe_cmd - *i] == 0)
		last_child(pip->cmds[*i], pip, p_fd, data);
	close(p_fd[0]);
	close(p_fd[1]);
	close_fds(pip);
}

int	pipex(t_pipeline *pip, t_data *data)
{
	int		p_fd[2];
	int		i;
	int		pipe_cmd;
	int		status;

	i = pip->start;
	pipe_cmd = pip->pipe_cnt + 1;
	signal(SIGPIPE, SIG_IGN);
	first_pipe(pip->cmds[i], pip, p_fd, data);
	i++;
	while (i < pipe_cmd - 1)
	{
		multi_pipe(pip, p_fd, data, &i);
		i++;
	}
	last_pipe(pip, p_fd, data, &i);
	i = pipe_cmd - i;
	while (i >= 0)
	{
		waitpid(pip->pid[i], &status, 0);
		i--;
	}
	if (WIFEXITED(status) && data->exit_code < 128)
		return (WEXITSTATUS(status));
	return (data->exit_code);
}

//ls | rev | << 1 cat | << 2 rev | cat -e