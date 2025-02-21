/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdemare <mdemare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 15:30:30 by mdemare           #+#    #+#             */
/*   Updated: 2025/02/21 18:13:55 by mdemare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*execute_checker(char **cmd, t_pipeline *pip, t_data *data)
{
	char	*cmd_path;

	if (!cmd || !cmd[0])
	{
		ft_print_error(NULL, NULL, "Invalid command");
		exit(127);
	}
	cmd_path = get_path(cmd[0], data->my_envp);
	if (!cmd_path)
	{
		ft_print_error(NULL, cmd[0], "command not found");
		free_execute(pip, data, cmd_path);
		exit(127);
	}
	if (ft_strstr(cmd[0], "./"))
	{
		free(cmd_path);
		cmd_path = cmd[0];
	}
	return (cmd_path);
}

static char	*cmd_path(char **cmd, t_pipeline *pip, t_data *data, char *cmd_path)
{
	if (ft_strstartwith(cmd[0], "./") && ft_strendwith(cmd[0], ".sh"))
	{
		script_checker(&cmd);
		if (!cmd_path)
			cmd_path = cmd[0];
	}
	else if (ft_strstartwith(cmd[0], "../") || ft_strcountchar(cmd[0], '.') > 2)
	{
		if (access(cmd[0], F_OK) == -1)
			ft_print_error(NULL, ft_strtok(cmd[0], " "), MSG_ERROR_FILE);
		else if (ft_strcountchar(cmd[0], '.') == 2)
			ft_print_error(NULL, ft_strtok(cmd[0], " "), MSG_IS_DIR);
		else
			ft_print_error(NULL, ft_strtok(cmd[0], " "), MSG_ERROR_FILE);
		free_execute(pip, data, cmd_path);
		exit(127);
	}
	else if ((ft_strstartwith(cmd[0], "./") && !ft_strendwith(cmd[0], ".sh"))
		|| (cmd[0][0] == '/' && access(cmd[0], R_OK) == -1))
	{
		ft_print_error(NULL, ft_strtok(cmd[0], " "), MSG_ERROR_FILE);
		free_execute(pip, data, cmd_path);
		exit(127);
	}
	return (cmd_path);
}

void	execute(char **cmd, t_pipeline *pip, t_data *data)
{
	char	*cmd_path_dir;

	cmd_path_dir = NULL;
	cmd_path_dir = cmd_path(cmd, pip, data, cmd_path_dir);
	if (!cmd_path_dir)
		cmd_path_dir = execute_checker(cmd, pip, data);
	if (cmd_path_dir)
	{
		execve(cmd_path_dir, cmd, data->my_envp);
		if (access(cmd_path_dir, F_OK) == 0)
		{
			if (access(cmd_path_dir, X_OK) == -1)
			{
				ft_print_error(NULL, cmd[0], "Permission denied");
				data->exit_code = 126;
				free_execute(pip, data, cmd_path_dir);
				exit(126);
			}
		}
		if (!ft_strstr(cmd[0], "./"))
			ft_print_error(NULL, cmd[0], "Execution error");
		data->exit_code = 127;
		free_execute(pip, data, cmd_path_dir);
		exit(127);
	}
}

static void	exec_child(t_pipeline *pip, t_data *data, pid_t	pid)
{
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
		execute(pip->cmds[pip->start]->args, pip, data);
	}
	if (pip->cmds[pip->start]->fd_in > -1)
		close(pip->cmds[pip->start]->fd_in);
	if (pip->cmds[pip->start]->fd_out > -1)
		close(pip->cmds[pip->start]->fd_out);
}

void	simple_exec(t_pipeline *pip, t_data *data)
{
	int		status;
	pid_t	pid;

	status = 0;
	if (pip->cmds[pip->start]->fd_out == -1
		|| pip->cmds[pip->start]->fd_in == -1)
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
