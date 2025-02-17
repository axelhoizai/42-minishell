/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoizai <ahoizai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 15:30:30 by mdemare           #+#    #+#             */
/*   Updated: 2025/02/17 13:37:52 by ahoizai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execute(char **cmd, t_pipeline *pip, t_data *data)
{
	char	*cmd_path;

	if (!cmd || !cmd[0])
	{
		// print_error("Invalid command", NULL, CMD_NOT_FOUND);
		ft_print_error(NULL, NULL, "Invalid command");
		free_term(data);
		exit(127);
	}
	cmd_path = get_path(cmd[0], data->my_envp);
	if (!cmd_path)
	{
		write(2, "command not found: ", 19);
		write(2, cmd[0], ft_strlen(cmd[0]));
		write(2, "\n", 1);
		ms_lstclear(&data->env_ms);
		free_tab(data->my_envp);
		free_term(data);
		free_pipeline(pip);
		exit(127);
	}
	if (ft_strstr(cmd[0], "./"))
	{
		free(cmd_path);
		cmd_path = cmd[0];
	}
	execve(cmd_path, cmd, data->my_envp);

	if (access(cmd_path, F_OK) == 0)
	{
		if (access(cmd_path, X_OK) == -1)
		{
			write(2, "Permission denied: ", 19);
			write(2, cmd[0], ft_strlen(cmd[0]));
			write(2, "\n", 1);
			free(cmd_path);
			ms_lstclear(&data->env_ms);
			free_tab(data->my_envp);
			free_term(data);
			free_pipeline(pip);
			exit(126);
		}
	}
	write(2, "Execution error: ", 17);
	write(2, cmd[0], ft_strlen(cmd[0]));
	write(2, "\n", 1);
	ms_lstclear(&data->env_ms);
	free_tab(data->my_envp);
	free_term(data);
	free_pipeline(pip);
	exit(127);
}

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
