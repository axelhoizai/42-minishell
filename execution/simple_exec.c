/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdemare <mdemare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 15:30:30 by mdemare           #+#    #+#             */
/*   Updated: 2025/02/20 09:33:21 by mdemare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_execute(t_pipeline *pip, t_data *data)
{
	ms_lstclear(&data->env_ms);
	free_tab(data->my_envp);
	free_term(data);
	free_pipeline(pip);
}

static char	*execute_checker(char **cmd, t_pipeline *pip, t_data *data)
{
	char	*cmd_path;

	if (!cmd || !cmd[0])
	{
		ft_print_error(NULL, NULL, "Invalid command");
		free_term(data);
		exit(127);
	}
	cmd_path = get_path(cmd[0], data->my_envp);
	if (!cmd_path)
	{
		ft_print_error(NULL, cmd[0], "command not found");
		free_execute(pip, data);
		exit(127);
	}
	if (ft_strstr(cmd[0], "./"))
	{
		free(cmd_path);
		cmd_path = cmd[0];
	}
	return (cmd_path);
}

void	execute(char **cmd, t_pipeline *pip, t_data *data)
{
	char	*cmd_path;

	if (ft_strstr(cmd[0], "./"))
		script_checker(cmd, cmd_path);
	else
		cmd_path = execute_checker(cmd, pip, data);
	execve(cmd_path, cmd, data->my_envp);
	if (access(cmd_path, F_OK) == 0)
	{
		if (access(cmd_path, X_OK) == -1)
		{
			ft_print_error(NULL, cmd[0], "Permission denied");
			free(cmd_path);
			free_execute(pip, data);
			exit(126);
		}
	}
	ft_print_error(NULL, cmd[0], "Execution error");
	free_execute(pip, data);
	exit(127);
}

static void	exec_child(t_pipeline *pip, t_data *data, pid_t	pid)
{
	// int	tty_fd;
	// tty_fd = -1;
	if (pid == 0)
	{
		if (pip->cmds[pip->start]->fd_in > -1)
		{
			dup2(pip->cmds[pip->start]->fd_in, STDIN_FILENO);
			close(pip->cmds[pip->start]->fd_in);
		}
		if (pip->cmds[pip->start]->fd_out > -1)
		{
			dup2(pip->cmds[pip->start]->fd_out, STDOUT_FILENO);
			close(pip->cmds[pip->start]->fd_out);
		}
		// if (!isatty(STDIN_FILENO)) // pour nano, vi, ...
		// {
		// 	tty_fd = open("/dev/tty", O_RDWR);
		// 	if (tty_fd > -1)
		// 	{
		// 		dup2(tty_fd, STDIN_FILENO);
		// 		close(tty_fd);
		// 	}
		// }
		execute(pip->cmds[pip->start]->args, pip, data);
	}
	if (pip->cmds[pip->start]->fd_in > -1)
		close(pip->cmds[pip->start]->fd_in);
	if (pip->cmds[pip->start]->fd_out > -1)
		close(pip->cmds[pip->start]->fd_out);
	// if (tty_fd > -1)
	// 	close(tty_fd);
}

void	simple_exec(t_pipeline *pip, t_data *data)
{
	int		status;
	pid_t	pid;

	status = 0;
	if (pip->cmds[pip->start]->fd_out == -1 || pip->cmds[pip->start]->fd_in == -1)
	{
		if (pip->cmds[pip->start]->fd_in > -1)
			close (pip->cmds[pip->start]->fd_in);
		data->exit_code = 1;
		return ;
	}
	if (pip->cmds[pip->start]->args)
	{
		pid = fork();
		if (pid == -1)
			exit(1);
		exec_child(pip, data, pid);
		waitpid(pid, &status, 0);
		if (WIFEXITED(status) && WEXITSTATUS(status) >= 0)
		{
			if (data->exit_code < 128)
				data->exit_code = WEXITSTATUS(status);
		}
	}
}
