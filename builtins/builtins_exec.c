/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdemare <mdemare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 15:30:30 by mdemare           #+#    #+#             */
/*   Updated: 2025/02/14 19:01:18 by mdemare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec(t_pipeline *pip, t_data *data)
{
	int		status;
	pid_t	pid[2];

	status = 0;
	if (pip->cmds[0]->fd_out == -1 || pip->cmds[0]->fd_in == -1)
	{
		if (pip->cmds[0]->fd_in > -1)
			close (pip->cmds[0]->fd_in);
		data->exit_code = 1;
		return ;
	}
	if (pip->cmds[0]->args)
	{
		pid[0] = fork();
		if (pid[0] == -1)
			exit(1);
		if (pid[0] == 0)
		{
			if (pip->cmds[0]->fd_in > -1)
			{
				dup2(pip->cmds[0]->fd_in, STDIN_FILENO);
				close(pip->cmds[0]->fd_in);
			}
			if (pip->cmds[0]->fd_out > -1)
			{
				dup2(pip->cmds[0]->fd_out, STDOUT_FILENO);
				close(pip->cmds[0]->fd_out);
			}
			execute(pip->cmds[0]->args, pip, data);
		}
		if (pip->cmds[0]->fd_in > -1)
			close(pip->cmds[0]->fd_in);
		if (pip->cmds[0]->fd_out > -1)
			close(pip->cmds[0]->fd_out);
		waitpid(pid[0], &status, 0);
		if (WIFEXITED(status) && WEXITSTATUS(status) >= 0)
		{
			if (data->exit_code < 128)
				data->exit_code = WEXITSTATUS(status);
		}
	}
}
